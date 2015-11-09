// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once


#include "ApplicationConfiguration.h"

#include <string>

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class IApplicationConfigurationVersionProvider
            {
            public:
                virtual ~IApplicationConfigurationVersionProvider() { }
                
                virtual std::string GetProductVersionString() const = 0;
                
                virtual std::string GetBuildNumberString() const = 0;
            };
        }
    }
}
