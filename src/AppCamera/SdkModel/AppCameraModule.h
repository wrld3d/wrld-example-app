// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IAppCameraModule.h"
#include "AppCamera.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            class AppCameraModule : public IAppCameraModule
            {
            public:
                
                AppCameraModule();
                ~AppCameraModule();
                
                IAppCameraController& GetController();
                
            private:
                
                IAppCameraController* m_pAppCameraController;
            };
        }
    }
}