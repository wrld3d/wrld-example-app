// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "UserInteractionModule.h"

// App includes
#include "UserInteractionController.h"
#include "UserInteractionModel.h"

//TODO: Add Observer after implementing

namespace ExampleApp
{
    namespace UserInteraction
    {
        namespace SdkModel
        {
            UserInteractionModule::UserInteractionModule(AppCamera::SdkModel::IAppCameraController& appCameraController,
                                                         CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController)
            {
                m_pUserInteractionModel = Eegeo_NEW(UserInteractionModel)();
                m_pUserInteractionController = Eegeo_NEW(UserInteractionController)(*m_pUserInteractionModel, appCameraController, cameraTransitionController);
            }
            
            UserInteractionModule::~UserInteractionModule()
            {
                Eegeo_DELETE m_pUserInteractionController;
                Eegeo_DELETE m_pUserInteractionModel;
            }
        }
    }
}