// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IApplicationConfigurationModule.h"
#include "ApplicationConfig.h"
#include "IFileIO.h"
#include "Config.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class ApplicationConfigurationModule : public IApplicationConfigurationModule, private Eegeo::NonCopyable
            {
                IApplicationConfigurationService* m_pApplicationConfigurationService;
                IApplicationConfigurationReader* m_pApplicationConfigurationReader;
                IApplicationConfigurationParser* m_pApplicationConfigurationParser;
                
            public:
                ApplicationConfigurationModule(Eegeo::Helpers::IFileIO& fileIO,
                                               const IApplicationConfigurationVersionProvider& applicationConfigurationVersionProvider);
                
                ~ApplicationConfigurationModule();
                
                IApplicationConfigurationService& GetApplicationConfigurationService();
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
