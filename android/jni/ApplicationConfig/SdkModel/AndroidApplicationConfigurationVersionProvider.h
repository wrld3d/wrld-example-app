// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IApplicationConfigurationVersionProvider.h"
#include "AndroidNativeState.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class AndroidApplicationConfigurationVersionProvider : public IApplicationConfigurationVersionProvider
            {
            public:
            	AndroidApplicationConfigurationVersionProvider(const AndroidNativeState& nativeState);
                
                std::string GetProductVersionString() const;

                std::string GetBuildNumberString() const;
            private:
                std::string m_productVersion;
                std::string m_buildNumber;
            };
        }
    }
}
