// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorId.h"
#include "VectorMath.h"
#include "RenderCamera.h"
#include "CameraHelpers.h"
#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"
#include "EnvironmentRayCaster.h"
#include "TerrainHeightProvider.h"
#include "InteriorInteractionModel.h"
#include "InteriorsCameraController.h"
#include "ICameraTransitionController.h"
#include "CollisionMeshResourceRepository.h"
#include "DoubleTapIndoorInteractionController.h"

namespace ExampleApp
{
    namespace DoubleTapIndoorInteraction
    {
        namespace SdkModel
        {
            DoubleTapIndoorInteractionController::DoubleTapIndoorInteractionController(Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                                                                                       ExampleApp::CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                                       Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                                       ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel,
                                                                                       Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                                                                       Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule,
                                                                                       AppCamera::SdkModel::IAppCameraController& iCameraController)
            :m_interiorsCameraController(interiorsCameraController),m_cameraTransitionController(cameraTransitionController),m_interiorInteractionModel(interiorInteractionModel),m_appModeModel(appModeModel),m_interiorTransitionModel(interiorTransitionModel),m_closeDistanceOffSet(10),m_optimizedDistanceOffSet(100),m_iCameraController(iCameraController)
            
            {
                m_pTerrainRayPicker = Eegeo_NEW(Eegeo::Resources::Terrain::Collision::TerrainRayPicker)(terrainModelModule.GetTerrainHeightProvider(), terrainModelModule.GetCollisionMeshResourceRepository());
            }
            DoubleTapIndoorInteractionController::~DoubleTapIndoorInteractionController()
            {
                Eegeo_DELETE m_pTerrainRayPicker;
            }
            
            void DoubleTapIndoorInteractionController::OnDoubleTap(const AppInterface::TapData& data)
            {

                float optimizedDistance = CalcRecommendedOverviewDistanceForFloor();
                float camerDistanceFrom = m_interiorsCameraController.GetDistanceToInterest();
                Eegeo::Resources::Interiors::InteriorId interiorID = m_interiorInteractionModel.GetInteriorModel()->GetId();

                float closeDistacne = CalculateCloseDistanceWithRespectTo(optimizedDistance);

                if ((camerDistanceFrom < optimizedDistance  && camerDistanceFrom >= (closeDistacne + m_closeDistanceOffSet)) || (camerDistanceFrom > optimizedDistance && camerDistanceFrom  < (optimizedDistance + m_optimizedDistanceOffSet)))
                {
                    ZoomIn(closeDistacne, data);
                }
                else
                {
                    ZoomIn(optimizedDistance, data);
                }

  
            }
            void DoubleTapIndoorInteractionController::ZoomIn(float distance,const AppInterface::TapData& data)
            {
                

                const Eegeo::Camera::RenderCamera& renderCamera = m_iCameraController.GetRenderCamera();
                float screenPixelX = data.point.GetX();
                float screenPixelY = data.point.GetY();
                
                Eegeo::dv3 rayDirection;
                Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);
//                const Eegeo::dv3& rayOrigin = renderCamera.GetEcefLocation();
                const Eegeo::dv3& rayOrigin = m_iCameraController.GetNonFlattenedCameraPosition();

                
                Eegeo::dv3 rayIntersectionPoint;
                double intersectionParam;
                float terrainHeight;
                float heightAboveTerrain;
                bool rayPick = PerformRayPick(rayOrigin, rayDirection, rayIntersectionPoint, intersectionParam, terrainHeight, heightAboveTerrain);
                
                if (rayPick)
                {
                    Eegeo::Resources::Interiors::InteriorId interiorID = m_interiorInteractionModel.GetInteriorModel()->GetId();
                    int selectedFloor = m_interiorInteractionModel.GetSelectedFloorIndex();
                    m_cameraTransitionController.StartTransitionTo(rayIntersectionPoint,distance, interiorID, selectedFloor);
                }
                
                
                
                
            
            }
            
            bool DoubleTapIndoorInteractionController::PerformRayPick(const Eegeo::dv3 &rayOrigin,
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
                    rayPick = m_pTerrainRayPicker->TryGetRayIntersection(rayOrigin, rayDirection, out_rayIntersectionPoint, out_intersectionParam);
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
            //TODO: This function will be removed when it will be exposed in SDK::InteroirHelper by dandee team
            float DoubleTapIndoorInteractionController::CalcRecommendedOverviewDistanceForFloor()
            {
                
                const Eegeo::Camera::RenderCamera& renderCamera = m_iCameraController.GetRenderCamera();
                const bool isLandscapeOrientation = renderCamera.GetAspect() > 1.0f;
                const float verticalFovRadians = renderCamera.GetFOV();
                const float horizontalFovRadians = isLandscapeOrientation ? verticalFovRadians * Eegeo::Camera::RenderCamera::NominalAspectRatio : verticalFovRadians * renderCamera.GetAspect();
                
                const Eegeo::Geometry::Bounds3D &bounds = m_interiorInteractionModel.GetSelectedFloorModel()->GetTangentSpaceBounds();
                
                float diagonalLength = Eegeo::v2(bounds.Size().x,bounds.Size().z).Length();

                return ((diagonalLength * 0.5f) / tanf(horizontalFovRadians*0.5f));



            
            }
            float DoubleTapIndoorInteractionController::CalculateCloseDistanceWithRespectTo(float optimizedDistance)
            {
                return optimizedDistance*0.36;
            }
            

        }
    }
}