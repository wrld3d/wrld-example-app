// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorId.h"
#include "VectorMath.h"
#include "RenderCamera.h"
#include "CameraHelpers.h"
#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"
#include "EnvironmentRayCaster.h"
#include "InteriorInteractionModel.h"
#include "InteriorsCameraController.h"
#include "ICameraTransitionController.h"
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
                                                                                       Eegeo::Collision::IRayCaster& rayCaster,
                                                                                       ExampleApp::AppModes::SdkModel::IAppModeModel& appModeModel):m_interiorsCameraController(interiorsCameraController),m_cameraTransitionController(cameraTransitionController),m_interiorInteractionModel(interiorInteractionModel),m_enovRayCaster(rayCaster),m_appModeModel(appModeModel),m_appModeChangedCallback(this, &DoubleTapIndoorInteractionController::OnAppModeChanged)
            {
                m_appModeModel.RegisterAppModeChangedCallback(m_appModeChangedCallback);
                m_states = Far;
            }
            DoubleTapIndoorInteractionController::~DoubleTapIndoorInteractionController()
            {
            }
            
            void DoubleTapIndoorInteractionController::OnDoubleTap(const AppInterface::TapData& data)
            {

                const Eegeo::Geometry::Bounds3D &bounds = m_interiorInteractionModel.GetSelectedFloorModel()->GetTangentSpaceBounds();
                const float fov = m_interiorsCameraController.GetRenderCamera().GetFOV();
                float optimizedDistance = CalcRecommendedOverviewDistanceForFloor(bounds,fov);

                if (m_states == Far)
                {
                    Eegeo::Resources::Interiors::InteriorId interiorID = m_interiorInteractionModel.GetInteriorModel()->GetId();
                    int selectedFloor = m_interiorInteractionModel.GetSelectedFloorIndex();
                    m_cameraTransitionController.StartTransitionTo(optimizedDistance, interiorID, selectedFloor);
                    m_states = Optimized;

                }
                else if(m_states == Optimized)
                {
                    float closeDistacne = CalculateCloseDistanceWithRespectTo(optimizedDistance);
                    ZoomInTo(closeDistacne, data);
                    m_states = Close;
                }
                else
                {

                    ZoomInTo(optimizedDistance, data);
                    m_states = Optimized;

                
                }

  
            }
            void DoubleTapIndoorInteractionController::ZoomInTo(float distance,const AppInterface::TapData& data)
            {
                
                Eegeo::Resources::Interiors::InteriorId interiorID = m_interiorInteractionModel.GetInteriorModel()->GetId();
                int selectedFloor = m_interiorInteractionModel.GetSelectedFloorIndex();
                const Eegeo::Camera::RenderCamera& renderCamera = m_interiorsCameraController.GetRenderCamera();
                
                float screenPixelX = data.point.GetX();
                float screenPixelY = data.point.GetY();
                
                
                Eegeo::dv3 rayDirection;
                Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);
                const Eegeo::dv3& rayOrigin = renderCamera.GetEcefLocation();
                const Eegeo::Collision::RayCasterResult& pickResult = m_enovRayCaster.CastRay(rayOrigin, rayDirection,Eegeo::Collision::CollisionGroup::CollideAll);
                m_cameraTransitionController.StartTransitionTo(pickResult.intersectionPointEcef,distance, interiorID, selectedFloor);
            
            }
            //TODO: This function will be removed when it will be exposed in SDK::InteroirHelper by dandee team
            float DoubleTapIndoorInteractionController::CalcRecommendedOverviewDistanceForFloor(const Eegeo::Geometry::Bounds3D& floorTangentSpaceBounds, float fieldOfViewRadians)
            {
                float diagonalLength = Eegeo::v2(floorTangentSpaceBounds.Size().x,floorTangentSpaceBounds.Size().z).Length();
                return ((diagonalLength * 0.5f) / tanf(fieldOfViewRadians*0.5f));
            
            }
            float DoubleTapIndoorInteractionController::CalculateCloseDistanceWithRespectTo(float optimizedDistance)
            {
                return optimizedDistance*0.5;
            }
            void DoubleTapIndoorInteractionController::OnAppModeChanged()
            {
                if (m_appModeModel.GetAppMode() == AppModes::SdkModel::InteriorMode)
                {
                    m_states = Far;
                }

            }

        }
    }
}