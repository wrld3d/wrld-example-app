// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfigurationService.h"
#include "IApplicationConfigurationParser.h"
#include "IApplicationConfigurationReader.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            ApplicationConfigurationService::ApplicationConfigurationService(IApplicationConfigurationParser& parser,
                                                                             IApplicationConfigurationReader& reader)
            : m_parser(parser)
            , m_reader(reader)
            {
                
            }
            
            ApplicationConfiguration ApplicationConfigurationService::LoadConfiguration(const std::string& path)
            {
                const std::string& serialized = m_reader.ReadApplicationConfiguration(path);
                return m_parser.ParseConfiguration(serialized);
            }
        }
    }
}
