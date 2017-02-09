// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PoiRingTouchController.h"
#include "CameraHelpers.h"
#include "RenderCamera.h"
#include "IMyPinCreationModel.h"
#include "GlobeCameraController.h"
#include "EarthConstants.h"
#include "IntersectionTests.h"
#include "IPoiRingController.h"
#include "IAppModeModel.h"
#include "InteriorsFloorModel.h"
#include "Bounds.h"
#include "InteriorsModel.h"
#include "EcefTangentBasis.h"
#include "InteriorHeightHelpers.h"
#include "InteriorInteractionModel.h"
#include "InteriorTransitionModel.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {

                namespace
                {
                    bool SphereIntersectsWithRay(const Eegeo::dv3& sphereCentre, double sphereRadius, const Eegeo::dv3& rayOrigin, const Eegeo::dv3& rayDirection, double &out_intersectionParam)
                    {
                        out_intersectionParam = 0.0;
                        Eegeo::dv3 m = rayOrigin - sphereCentre;
                        double b = Eegeo::dv3::Dot(m, rayDirection);
                        double c = Eegeo::dv3::Dot(m, m) - sphereRadius*sphereRadius;
                        if (c > 0.0 && b > 0.0)
                            return false;
                        float discr = b*b - c;
                        if (discr < 0.0)
                            return false;
                        double t = -b - std::sqrt(discr);
                        t = std::max(t, 0.0);

                        out_intersectionParam = t;

                        return true;
                    }
                }

                PoiRingTouchController::PoiRingTouchController(MyPinCreation::SdkModel::IMyPinCreationModel& myPinCreationModel,
                                                               Eegeo::Collision::IRayPicker& rayPicker,
                                                               const IPoiRingController& poiRingController,
                                                               ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                               const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                               const Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel)
                    : m_myPinCreationModel(myPinCreationModel)
                    , m_rayPicker(rayPicker)
                    , m_poiRingController(poiRingController)
                    , m_isDragging(false)
                    , m_appModeModel(appModeModel)
                    , m_interiorInteractionModel(interiorInteractionModel)
                    , m_interiorTransitionModel(interiorTransitionModel)
                {

                }

                bool PoiRingTouchController::HandleTouchDown(const AppInterface::TouchData& data, const Eegeo::Camera::RenderCamera& renderCamera, const Eegeo::dv3& nonFlattenedCameraPosition)
                {
                    if (m_myPinCreationModel.GetCreationStage() != Ring)
                    {
                        return false;
                    }
                    
                    return TouchDownRaycast(data, renderCamera, nonFlattenedCameraPosition);
                }
                
                bool PoiRingTouchController::HandleTouchUp(const AppInterface::TouchData& data)
                {
                    m_isDragging = false;
                    
                    if (m_myPinCreationModel.GetCreationStage() != Ring)
                    {
                        return false;
                    }
                    
                    return true;
                }
            
                
                bool PoiRingTouchController::TouchDownRaycast(const AppInterface::TouchData &data,
                                                              const Eegeo::Camera::RenderCamera &renderCamera,
                                                              const Eegeo::dv3 &rayOrigin)
                {
                    float screenPixelX = data.point.GetX();
                    float screenPixelY = data.point.GetY();
                    
                    Eegeo::dv3 rayDirection;
                    Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);

                    Eegeo::dv3 rayIntersectionPoint;
                    double environemntIntersectionParam;
                    float terrainHeight;
                    float heightAboveTerrain;
                    const bool intersectsEnvironment = PerformRayPick(rayOrigin, rayDirection, rayIntersectionPoint, environemntIntersectionParam, terrainHeight, heightAboveTerrain);

                    if (intersectsEnvironment)
                    {
                        Eegeo::dv3 iconPosition;
                        float iconSize;
                        m_poiRingController.GetIconPositionAndSize(iconPosition, iconSize);
                        
                        Eegeo::dv3 spherePosition;
                        float sphereRadius;
                        m_poiRingController.GetSpherePositionAndRadius(spherePosition, sphereRadius);
                        
                        m_initialCameraAltitiude =  renderCamera.GetAltitude();
                        
                        bool hitIcon = Eegeo::Geometry::IntersectionTests::TestRaySphere(rayOrigin, rayDirection, iconPosition, iconSize/2.0f);

                        double sphereIntersectionParam = 0.0;                        
                        const bool hitSphere = SphereIntersectsWithRay(spherePosition, sphereRadius, rayOrigin, rayDirection, sphereIntersectionParam);

                        const double epsilon = 1e-4*sphereRadius;
                        const bool hitSphereBeforeEnvironment = hitSphere && ((sphereIntersectionParam - environemntIntersectionParam) < epsilon);

                        if (hitSphereBeforeEnvironment || hitIcon)
                        {
                            m_dragOffset = rayIntersectionPoint - spherePosition;
                            m_isDragging = true;
                            return true;
                        }
                    }
                    
                    return false;
                }
                
                bool PoiRingTouchController::TouchMoveRaycast(const AppInterface::TouchData &data,
                                                              const Eegeo::Camera::RenderCamera &renderCamera,
                                                              const Eegeo::dv3 &rayOrigin)
                {
                    m_isDragging = false;
                    m_dragOffset = Eegeo::dv3();

                    if (m_myPinCreationModel.GetCreationStage() != Ring)
                    {
                        return false;
                    }

                    return true;
                }

                bool PoiRingTouchController::HandleTouchMove(const AppInterface::TouchData &data, const Eegeo::Camera::RenderCamera &renderCamera, const Eegeo::dv3& nonFlattenedCameraPosition)
                {
                    if (m_myPinCreationModel.GetCreationStage() != Ring)
                    {
                        return false;
                    }

                    if (m_isDragging)
                    {
                        float screenPixelX = data.point.GetX();
                        float screenPixelY = data.point.GetY();
                        
                        Eegeo::dv3 rayDirection;
                        Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);

                        Eegeo::dv3 rayOrigin = nonFlattenedCameraPosition;
                        Eegeo::dv3 rayIntersectionPoint;
                        double intersectionParam;
                        float terrainHeight;
                        float heightAboveTerrain;
                        bool rayPick = PerformRayPick(rayOrigin, rayDirection, rayIntersectionPoint, intersectionParam, terrainHeight, heightAboveTerrain);
                        
                        if (rayPick)
                        {
                            const float currentCameraAltitiude = renderCamera.GetAltitude();
                            
                            float offsetScale = 0.0f;
                            if(currentCameraAltitiude != 0.0f && m_initialCameraAltitiude != 0.0f)
                            {
                                offsetScale = currentCameraAltitiude /m_initialCameraAltitiude;
                            }
                            
                            Eegeo::Space::LatLong latLong = Eegeo::Space::LatLong::FromECEF(rayIntersectionPoint - (m_dragOffset * offsetScale));
                            m_myPinCreationModel.SetLatLong(latLong);
                            m_myPinCreationModel.SetTerrainHeight(terrainHeight);
                            m_myPinCreationModel.SetHeightAboveTerrain(heightAboveTerrain);
                        }
                        
                        return true;
                    }
                    
                    return false;
                }
                
                bool PoiRingTouchController::IsDragging() const
                {
                    return m_isDragging && m_myPinCreationModel.GetCreationStage() == Ring;
                }

                bool PoiRingTouchController::PerformRayPick(const Eegeo::dv3 &rayOrigin,
                                                            Eegeo::dv3 &rayDirection,
                                                            Eegeo::dv3 &out_rayIntersectionPoint,
                                                            double &out_intersectionParam,
                                                            float &out_terrainHeight,
                                                            float &out_heightAboveTerrain)
                {
                    bool rayPick = false;

                    if(m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode && m_interiorTransitionModel.InteriorIsVisible())
                    {
                        const Eegeo::Resources::Interiors::InteriorsModel* interiorsModel = m_interiorInteractionModel.GetInteriorModel();
                        
                        Eegeo_ASSERT(interiorsModel, "Couldn't get current interiorsModel");
                        
                        const Eegeo::dv3 originNormal = interiorsModel->GetTangentBasis().GetUp();
                        
                        const int selectedFloorIndex = m_interiorInteractionModel.GetSelectedFloorIndex();

                        float floorHeightAboveSeaLevel = Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevel(*interiorsModel, selectedFloorIndex);
                        
                        const Eegeo::dv3 point = originNormal * (floorHeightAboveSeaLevel + Eegeo::Space::EarthConstants::Radius);
                        
                        out_terrainHeight = interiorsModel->GetTangentSpaceBounds().GetMin().y;
                        out_heightAboveTerrain = floorHeightAboveSeaLevel - out_terrainHeight;
                        rayPick = Eegeo::Geometry::IntersectionTests::RayIntersectsWithPlane(rayOrigin, rayDirection, originNormal, point, out_intersectionParam, out_rayIntersectionPoint);
                    }
                    else
                    {
                        rayPick = m_rayPicker.TryGetRayIntersection(rayOrigin, rayDirection, out_rayIntersectionPoint, out_intersectionParam);
                        if(rayPick)
                        {
                            out_terrainHeight = static_cast<float>(out_rayIntersectionPoint.Length() - Eegeo::Space::EarthConstants::Radius);
                            out_heightAboveTerrain = 0.0f;
                        }
                    }
                    if(!rayPick)
                    {
                        rayPick = Eegeo::Geometry::IntersectionTests::GetRayEarthSphereIntersection(rayOrigin, rayDirection, out_rayIntersectionPoint, Eegeo::Space::EarthConstants::RadiusSquared);
                        if(rayPick)
                        {
                            out_terrainHeight = 0.0f;
                            out_heightAboveTerrain = 0.0f;
                            out_intersectionParam = (out_rayIntersectionPoint - rayOrigin).Length();
                        }
                    }

                    return rayPick;
                }
            }
        }
    }
}
