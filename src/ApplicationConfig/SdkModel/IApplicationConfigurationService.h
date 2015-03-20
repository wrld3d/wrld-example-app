// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "ApplicationConfiguration.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class IApplicationConfigurationService
            {
            public:
                virtual ~IApplicationConfigurationService() { }
                
                virtual ApplicationConfiguration LoadConfiguration(const std::string& path) = 0;
            };
        }
    }
}
