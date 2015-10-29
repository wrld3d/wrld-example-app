// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "UserInteractionController.h"

// App includes
#include "IAppCameraController.h"
#include "ICameraTransitionController.h"
#include "UserInteractionModel.h"

namespace ExampleApp
{
    namespace UserInteraction
    {
        namespace SdkModel
        {
            UserInteractionController::UserInteractionController(UserInteractionModel& userInteractionModel,
                                                                 AppCamera::SdkModel::IAppCameraController& appCameraController,
                                                                 CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController)
            : m_userInteractionModel(userInteractionModel)
            , m_appCameraController(appCameraController)
            , m_cameraTransitionController(cameraTransitionController)
            , m_cameraTransitionChangedHandler(this, &UserInteractionController::OnCameraTransitionChanged)
            {
                m_cameraTransitionController.InsertTransitioningChangedCallback(m_cameraTransitionChangedHandler);
                m_appCameraController.InsertTransitioInFlightChangedCallback(m_cameraTransitionChangedHandler);
            }
            
            UserInteractionController::~UserInteractionController()
            {
                m_cameraTransitionController.RemoveTransitioningChangedCallback(m_cameraTransitionChangedHandler);
                m_appCameraController.RemoveTransitioInFlightChangedCallback(m_cameraTransitionChangedHandler);
            }
            
            void UserInteractionController::OnCameraTransitionChanged()
            {
                m_userInteractionModel.SetEnabled(!m_cameraTransitionController.IsTransitioning() && !m_appCameraController.IsTransitionInFlight());
            }
        }
    }
}