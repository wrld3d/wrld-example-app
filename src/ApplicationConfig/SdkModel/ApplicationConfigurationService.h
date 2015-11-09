// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IApplicationConfigurationService.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class ApplicationConfigurationService : public IApplicationConfigurationService, private Eegeo::NonCopyable
            {
                IApplicationConfigurationParser& m_parser;
                IApplicationConfigurationReader& m_reader;
                const std::string m_productVersion;
                const std::string m_buildNumber;
                
            public:
                ApplicationConfigurationService(IApplicationConfigurationParser& parser,
                                                IApplicationConfigurationReader& reader,
                                                const std::string& productVersion,
                                                const std::string& buildNumber);
                
                ApplicationConfiguration LoadConfiguration(const std::string& path);
            };
        }
    }
}
