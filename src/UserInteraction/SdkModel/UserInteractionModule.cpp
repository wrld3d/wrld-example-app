// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "UserInteractionModule.h"

// App includes
#include "UserInteractionController.h"
#include "UserInteractionEnabledObserver.h"
#include "UserInteractionModel.h"

namespace ExampleApp
{
    namespace UserInteraction
    {
        namespace SdkModel
        {
            UserInteractionModule::UserInteractionModule(AppCamera::SdkModel::IAppCameraController& appCameraController,
                                                         CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                                         InteriorsExplorer::SdkModel::InteriorExplorerUserInteractionModel& interiorExplorerUserInteractionModel,
                                                         ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pUserInteractionModel = Eegeo_NEW(UserInteractionModel)();
                
                m_pUserInteractionController = Eegeo_NEW(UserInteractionController)(*m_pUserInteractionModel,
                                                                                    appCameraController,
                                                                                    interiorExplorerUserInteractionModel,
                                                                                    cameraTransitionController);
                
                m_pUserInteractionEnabledObserver = Eegeo_NEW(UserInteractionEnabledObserver)(*m_pUserInteractionModel, messageBus);
            }
            
            UserInteractionModule::~UserInteractionModule()
            {
                Eegeo_DELETE m_pUserInteractionEnabledObserver;
                Eegeo_DELETE m_pUserInteractionController;
                Eegeo_DELETE m_pUserInteractionModel;
            }
            
            const UserInteractionModel& UserInteractionModule::GetUserInteractionModel() const
            {
                return *m_pUserInteractionModel;
            }
        }
    }
}