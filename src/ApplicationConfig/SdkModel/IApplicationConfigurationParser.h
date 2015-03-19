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
            class IApplicationConfigurationParser
            {
            public:
                virtual ~IApplicationConfigurationParser() { }
                
                virtual ApplicationConfiguration ParseConfiguration(const std::string& serialized) = 0;
            };
        }
    }
}
