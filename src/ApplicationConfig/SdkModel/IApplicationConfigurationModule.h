// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ApplicationConfig.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class IApplicationConfigurationModule
            {
            public:
                virtual ~IApplicationConfigurationModule() { }
                
                virtual IApplicationConfigurationService& GetApplicationConfigurationService() = 0;
            };
        }
    }
}
