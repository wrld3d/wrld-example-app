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
                const std::shared_ptr<IApplicationConfigurationParser> m_parser;
                const std::shared_ptr<IApplicationConfigurationReader> m_reader;
                
            public:
                ApplicationConfigurationService(const std::shared_ptr<IApplicationConfigurationParser>& parser,
                                                const std::shared_ptr<IApplicationConfigurationReader>& reader);
                
                ApplicationConfiguration LoadConfiguration(const std::string& path);
            };
        }
    }
}
