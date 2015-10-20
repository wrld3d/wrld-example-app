// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppCameraModule.h"
#include "AppCameraController.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            AppCameraModule::AppCameraModule()
            {
                m_pAppCameraController = Eegeo_NEW(AppCameraController)();
            
            }
            
            AppCameraModule::~AppCameraModule()
            {
                Eegeo_DELETE m_pAppCameraController;
                m_pAppCameraController = NULL;
            }
            
            IAppCameraController& AppCameraModule::GetController()
            {
                return *m_pAppCameraController;
            }
            
        }
    }
}
