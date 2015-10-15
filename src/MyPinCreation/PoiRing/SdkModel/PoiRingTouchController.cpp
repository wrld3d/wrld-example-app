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
#include "InteriorsController.h"
#include "InteriorsFloorModel.h"
#include "Bounds.h"
#include "InteriorsModel.h"
#include "EcefTangentBasis.h"
#include "InteriorHeightHelpers.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace PoiRing
        {
            namespace SdkModel
            {
                PoiRingTouchController::PoiRingTouchController(MyPinCreation::SdkModel::IMyPinCreationModel& myPinCreationModel,
                                                               Eegeo::Collision::IRayPicker& rayPicker,
                                                               const IPoiRingController& poiRingController,
                                                               ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                               Eegeo::Resources::Interiors::InteriorsController& interiorsController)
                    : m_myPinCreationModel(myPinCreationModel)
                    , m_rayPicker(rayPicker)
                    , m_poiRingController(poiRingController)
                    , m_isDragging(false)
                    , m_appModeModel(appModeModel)
                    , m_interiorsController(interiorsController)
                {

                }

                bool PoiRingTouchController::HandleTouchDown(const AppInterface::TouchData& data,
                                                             const Eegeo::Camera::RenderCamera& renderCamera,
                                                             Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
                {
                    if (m_myPinCreationModel.GetCreationStage() != Ring)
                    {
                        return false;
                    }
                    
                    
                    Eegeo::dv3 rayOrigin = globeCameraController.ComputeNonFlattenedCameraPosition();
                    
                    return TouchDownRaycast(data, renderCamera, rayOrigin);
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
                
                bool PoiRingTouchController::HandleTouchMove(const AppInterface::TouchData &data, const Eegeo::Camera::RenderCamera &renderCamera, Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController)
                {
                    if (m_myPinCreationModel.GetCreationStage() != Ring)
                    {
                        return false;
                    }
                    
                    Eegeo::dv3 rayOrigin = globeCameraController.ComputeNonFlattenedCameraPosition();
                    
                    return TouchMoveRaycast(data, renderCamera, rayOrigin);
                }
                
                bool PoiRingTouchController::HandleTouchDown(const AppInterface::TouchData& data,
                                                             const Eegeo::Camera::RenderCamera& renderCamera)
                {
                    if (m_myPinCreationModel.GetCreationStage() != Ring)
                    {
                        return false;
                    }
                    
                    
                    Eegeo::dv3 rayOrigin = renderCamera.GetEcefLocation();
                    
                    return TouchDownRaycast(data, renderCamera, rayOrigin);
                }
                
                bool PoiRingTouchController::HandleTouchMove(const AppInterface::TouchData &data,
                                                             const Eegeo::Camera::RenderCamera &renderCamera)
                {
                    if (m_myPinCreationModel.GetCreationStage() != Ring)
                    {
                        return false;
                    }
                    
                    Eegeo::dv3 rayOrigin = renderCamera.GetEcefLocation();
                    
                    return TouchMoveRaycast(data, renderCamera, rayOrigin);
                }
                
                bool PoiRingTouchController::TouchDownRaycast(const AppInterface::TouchData &data,
                                                              const Eegeo::Camera::RenderCamera &renderCamera, Eegeo::dv3 &rayOrigin)
                {
                    float screenPixelX = data.point.GetX();
                    float screenPixelY = data.point.GetY();
                    
                    Eegeo::dv3 rayDirection;
                    Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);
                    
                    Eegeo::dv3 rayIntersectionPoint;
                    double intersectionParam;
                    
                    bool rayPick = PerformRayPick(rayOrigin, rayDirection, rayIntersectionPoint, intersectionParam);
                    
                    if (rayPick)
                    {
                        Eegeo::dv3 iconPosition;
                        float iconSize;
                        m_poiRingController.GetIconPositionAndSize(iconPosition, iconSize);
                        
                        Eegeo::dv3 spherePosition;
                        float sphereRadius;
                        m_poiRingController.GetSpherePositionAndRadius(spherePosition, sphereRadius);
                        
                        bool hitIcon = Eegeo::Geometry::IntersectionTests::TestRaySphere(rayOrigin, rayDirection, iconPosition, iconSize/2.0f);
                        if ((rayIntersectionPoint - spherePosition).Length() < sphereRadius || hitIcon)
                        {
                            m_isDragging = true;
                            return true;
                        }
                    }
                    
                    return false;
                }
                
                bool PoiRingTouchController::TouchMoveRaycast(const AppInterface::TouchData &data,
                                                              const Eegeo::Camera::RenderCamera &renderCamera, Eegeo::dv3 &rayOrigin)
                {
                    if (m_isDragging)
                    {
                        float screenPixelX = data.point.GetX();
                        float screenPixelY = data.point.GetY();
                        
                        Eegeo::dv3 rayDirection;
                        Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);
                        
                        Eegeo::dv3 rayIntersectionPoint;
                        double intersectionParam;
                        bool rayPick = PerformRayPick(rayOrigin, rayDirection, rayIntersectionPoint, intersectionParam);
                        
                        if (rayPick)
                        {
                            m_myPinCreationModel.SetPosition(rayIntersectionPoint);
                        }
                        
                        return true;
                    }
                    
                    return false;
                }
                
                bool PoiRingTouchController::IsDragging() const
                {
                    return m_isDragging && m_myPinCreationModel.GetCreationStage() == Ring;
                }

                bool PoiRingTouchController::PerformRayPick(Eegeo::dv3 &rayOrigin, Eegeo::dv3 &rayDirection, Eegeo::dv3 &out_rayIntersectionPoint, double &out_intersectionParam)
                {
                    bool rayPick = false;
                    
                    if(m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode && m_interiorsController.InteriorIsVisible())
                    {
                        const Eegeo::Resources::Interiors::InteriorsModel* interiorsModel;
                        
                        Eegeo_ASSERT(m_interiorsController.TryGetCurrentModel(interiorsModel), "Couldn't get current interiorsModel");
                        
                        const Eegeo::dv3 originNormal = interiorsModel->GetTangentBasis().GetUp();
                        
                        float floorHeightAboveSeaLevel = Helpers::InteriorHeightHelpers::GetFloorHeightAboveSeaLevel(*interiorsModel, m_interiorsController.GetCurrentFloorIndex());
                        
                        const Eegeo::dv3 point = originNormal * (floorHeightAboveSeaLevel + Eegeo::Space::EarthConstants::Radius);
                        
                        rayPick = Eegeo::Geometry::IntersectionTests::RayIntersectsWithPlane(rayOrigin, rayDirection, originNormal, point, out_intersectionParam, out_rayIntersectionPoint);
                    }
                    else
                    {
                        rayPick = m_rayPicker.TryGetRayIntersection(rayOrigin, rayDirection, out_rayIntersectionPoint, out_intersectionParam);
                    }
                    if(!rayPick)
                    {
                        rayPick = Eegeo::Geometry::IntersectionTests::GetRayEarthSphereIntersection(rayOrigin, rayDirection, out_rayIntersectionPoint, Eegeo::Space::EarthConstants::RadiusSquared);
                        if(rayPick)
                        {
                            out_intersectionParam = (out_rayIntersectionPoint - rayOrigin).Length();
                        }
                    }

                    return rayPick;
                }
            }
        }
    }
}
