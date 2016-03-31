// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "IApplicationConfigurationVersionProvider.h"
#include "Types.h"


namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class WindowsApplicationConfigurationVersionProvider : public IApplicationConfigurationVersionProvider, private Eegeo::NonCopyable
            {
            public:
                WindowsApplicationConfigurationVersionProvider();

                std::string GetProductVersionString() const;

                std::string GetBuildNumberString() const;
            private:
                std::string m_productVersion;
                std::string m_buildNumber;
            };
        }
    }
}