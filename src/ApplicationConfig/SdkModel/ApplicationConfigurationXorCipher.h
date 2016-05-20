// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ApplicationConfig.h"
#include "IApplicationConfigurationCipher.h"
#include "Types.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {

            class ApplicationConfigurationXorCipher : public IApplicationConfigurationCipher, private Eegeo::NonCopyable
            {
            public:
                ApplicationConfigurationXorCipher(const std::string& key);

                std::string Encrypt(const std::string& message) const;
                std::string Decrypt(const std::string& message) const;

            private:
                const std::string m_key;

            };
        }
    }
}
