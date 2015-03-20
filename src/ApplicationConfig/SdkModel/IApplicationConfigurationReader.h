// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class IApplicationConfigurationReader
            {
            public:
                virtual ~IApplicationConfigurationReader() { }
                
                virtual std::string ReadApplicationConfiguration(const std::string& pathToConfiguration) = 0;
            };
        }
    }
}
