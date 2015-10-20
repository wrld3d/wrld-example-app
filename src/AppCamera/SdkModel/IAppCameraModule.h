// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "AppCamera.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            class IAppCameraModule : private Eegeo::NonCopyable
            {
            public:
                
                virtual ~IAppCameraModule() {}
                
                virtual IAppCameraController& GetController() = 0;
            };
        }
    }
}