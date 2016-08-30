// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorId.h"
#include "RenderCamera.h"
#include "CameraHelpers.h"
#include "InteriorsModel.h"
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
            DoubleTapIndoorInteractionController::DoubleTapIndoorInteractionController(const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsCameraController>& interiorsCameraController,
                                                                                       const std::shared_ptr<ExampleApp::CameraTransitions::SdkModel::ICameraTransitionController>& cameraTransitionController,
                                                                                       const std::shared_ptr<Eegeo::Resources::Interiors::InteriorInteractionModel>& interiorInteractionModel,
                                                                                       const std::shared_ptr<Eegeo::Collision::IRayCaster>& rayCaster)
            : m_interiorsCameraController(interiorsCameraController)
            , m_cameraTransitionController(cameraTransitionController)
            , m_interiorInteractionModel(interiorInteractionModel)
            , m_enovRayCaster(rayCaster)
            {
            
            }
            
            DoubleTapIndoorInteractionController::~DoubleTapIndoorInteractionController()
            {
            }
            
            void DoubleTapIndoorInteractionController::OnDoubleTap(const AppInterface::TapData& data)
            {
                const float ClosestDistance = 80.f;
                const float OptimisedDistance = 300.f;
                if (m_interiorsCameraController->GetDistanceToInterest() <= ClosestDistance)
                {
                    Eegeo::Resources::Interiors::InteriorId interiorID = m_interiorInteractionModel->GetInteriorModel()->GetId();
                    int selectedFloor = m_interiorInteractionModel->GetSelectedFloorIndex();
                    m_cameraTransitionController->StartTransitionTo(OptimisedDistance, interiorID, selectedFloor);

                }
                else if(m_interiorsCameraController->GetDistanceToInterest() <= OptimisedDistance)
                {
                    ZoomInTo(ClosestDistance, data);
                }
                else
                {
                    ZoomInTo(OptimisedDistance, data);
                }
            }
            
            void DoubleTapIndoorInteractionController::ZoomInTo(float distance,const AppInterface::TapData& data)
            {
                Eegeo::Resources::Interiors::InteriorId interiorID = m_interiorInteractionModel->GetInteriorModel()->GetId();
                int selectedFloor = m_interiorInteractionModel->GetSelectedFloorIndex();
                const Eegeo::Camera::RenderCamera& renderCamera = m_interiorsCameraController->GetRenderCamera();
                
                float screenPixelX = data.point.GetX();
                float screenPixelY = data.point.GetY();
                
                Eegeo::dv3 rayDirection;
                Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPixelX, screenPixelY, rayDirection);
                const Eegeo::dv3& rayOrigin = renderCamera.GetEcefLocation();
                const Eegeo::Collision::RayCasterResult& pickResult = m_enovRayCaster->CastRay(rayOrigin, rayDirection,Eegeo::Collision::CollisionGroup::CollideAll);
                m_cameraTransitionController->StartTransitionTo(pickResult.intersectionPointEcef,distance, interiorID, selectedFloor);
            }
        }
    }
}