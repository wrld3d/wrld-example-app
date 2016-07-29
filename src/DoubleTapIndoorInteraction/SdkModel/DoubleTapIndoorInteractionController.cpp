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


// #TODO: We shall move these macros in constant or conif file.
#define CLOSEST_DISTANCE 80
#define OPTIMIZED_DISTANCE 300
namespace ExampleApp
{
    namespace DoubleTapIndoorInteraction
    {
        namespace SdkModel
        {
            DoubleTapIndoorInteractionController::DoubleTapIndoorInteractionController(Eegeo::Resources::Interiors::InteriorsCameraController& interiorsCameraController,
                                                                                       ExampleApp::CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                                                       Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                                       Eegeo::Collision::IRayCaster& rayCaster):m_interiorsCameraController(interiorsCameraController),m_cameraTransitionController(cameraTransitionController),m_interiorInteractionModel(interiorInteractionModel),m_enovRayCaster(rayCaster)
            {
            
            }
            DoubleTapIndoorInteractionController::~DoubleTapIndoorInteractionController()
            {
            }
            
            void DoubleTapIndoorInteractionController::OnDoubleTap(const AppInterface::TapData& data)
            {


                if (m_interiorsCameraController.GetDistanceToInterest() <= CLOSEST_DISTANCE)
                {
                    Eegeo::Resources::Interiors::InteriorId interiorID = m_interiorInteractionModel.GetInteriorModel()->GetId();
                    int selectedFloor = m_interiorInteractionModel.GetSelectedFloorIndex();
                    m_cameraTransitionController.StartTransitionTo(OPTIMIZED_DISTANCE, interiorID, selectedFloor);

                }
                else if(m_interiorsCameraController.GetDistanceToInterest() <= OPTIMIZED_DISTANCE)
                {
                    ZoomInTo(CLOSEST_DISTANCE, data);
                }
                else
                {
                    ZoomInTo(OPTIMIZED_DISTANCE, data);
                
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


        }
    }
}