// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "UserInteractionController.h"

// App includes
#include "IAppCameraController.h"
#include "ICameraTransitionController.h"
#include "InteriorExplorerUserInteractionModel.h"
#include "UserInteractionModel.h"

namespace ExampleApp
{
    namespace UserInteraction
    {
        namespace SdkModel
        {
            UserInteractionController::UserInteractionController(const std::shared_ptr<UserInteractionModel>& userInteractionModel,
                                                                 const std::shared_ptr<AppCamera::SdkModel::IAppCameraController>& appCameraController,
                                                                 const std::shared_ptr<InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel>& interiorExplorerUserInteractionModel,
                                                                 const std::shared_ptr<CameraTransitions::SdkModel::ICameraTransitionController>& cameraTransitionController)
            : m_userInteractionModel(userInteractionModel)
            , m_appCameraController(appCameraController)
            , m_cameraTransitionController(cameraTransitionController)
            , m_interiorExplorerUserInteractionModel(interiorExplorerUserInteractionModel)
            , m_handler(this, &UserInteractionController::OnObservedChanged)
            {
                m_cameraTransitionController->InsertTransitioningChangedCallback(m_handler);
                m_appCameraController->InsertTransitioInFlightChangedCallback(m_handler);
                m_interiorExplorerUserInteractionModel->InsertEnabledChangedCallback(m_handler);
            }
            
            UserInteractionController::~UserInteractionController()
            {
                m_cameraTransitionController->RemoveTransitioningChangedCallback(m_handler);
                m_appCameraController->RemoveTransitioInFlightChangedCallback(m_handler);
                m_interiorExplorerUserInteractionModel->RemoveEnabledChangedCallback(m_handler);
            }
            
            void UserInteractionController::OnObservedChanged()
            {
                m_userInteractionModel->SetEnabled(!m_cameraTransitionController->IsTransitioning() &&
                                                  !m_appCameraController->IsTransitionInFlight() &&
                                                  m_interiorExplorerUserInteractionModel->IsEnabled());
            }
        }
    }
}