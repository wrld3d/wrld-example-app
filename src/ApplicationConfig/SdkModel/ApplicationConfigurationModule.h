// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IModule.h"
#include "Types.h"
#include "ApplicationConfiguration.h"
#include "IPlatformConfigBuilder.h"
#include "IFileIO.h"
#include <string>

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class ApplicationConfigurationModule : public IModule, private Eegeo::NonCopyable
            {
            public:
                ApplicationConfigurationModule(const ApplicationConfiguration& defaultConfig);
                void Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder);
            private:
                ApplicationConfiguration m_default;
            };
            
            ApplicationConfig::ApplicationConfiguration LoadAppConfig(Eegeo::Helpers::IFileIO& fileIO,
                                                                      ApplicationConfig::SdkModel::IApplicationConfigurationVersionProvider& applicationConfigurationVersionProvider,
                                                                      const std::string& configFilePath
                                                                      );
            
            Eegeo::Config::PlatformConfig BuildPlatformConfig(Eegeo::Config::IPlatformConfigBuilder& platformConfigBuilder,
                                                              const ApplicationConfiguration& appConfig);
        }
    }
}
