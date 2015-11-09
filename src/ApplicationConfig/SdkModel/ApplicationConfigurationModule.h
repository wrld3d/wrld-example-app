// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IApplicationConfigurationModule.h"
#include "ApplicationConfig.h"
#include "IFileIO.h"

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
                IApplicationConfigurationBuilder* m_pApplicationConfigurationBuilder;
                
            public:
                ApplicationConfigurationModule(Eegeo::Helpers::IFileIO& fileIO,
                                               const std::string& productVersion,
                                               const std::string& buildNumber);
                
                ~ApplicationConfigurationModule();
                
                IApplicationConfigurationService& GetApplicationConfigurationService();
            };
        }
    }
}
