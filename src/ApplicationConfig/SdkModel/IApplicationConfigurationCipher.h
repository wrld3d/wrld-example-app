// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ApplicationConfig.h"
#include "Types.h"

#include <string>

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {

            class IApplicationConfigurationCipher
            {
            public:
                virtual ~IApplicationConfigurationCipher() { ; }

                virtual std::string Encrypt(const std::string& message) const = 0;
                virtual std::string Decrypt(const std::string& message) const = 0;
            };
        }
    }
}
