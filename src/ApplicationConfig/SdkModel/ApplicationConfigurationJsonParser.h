// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ApplicationConfig.h"
#include "IApplicationConfigurationParser.h"
#include "Types.h"
#include "document.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class ApplicationConfigurationJsonParser : public IApplicationConfigurationParser, private Eegeo::NonCopyable
            {
            public:
                ApplicationConfigurationJsonParser(const ApplicationConfiguration& defaultConfig);

                ApplicationConfiguration ParseConfiguration(const std::string& serialized);
                bool IsValidConfig(const std::string& serialized);
                bool HasKey(const std::string& serialized, const std::string& key);
                static std::vector<ApplicationMenuItemTagSearchConfig> ParseSearchMenuConfig(const rapidjson::Value& valueArray);
            private:
                const ApplicationConfiguration m_defaultConfig;
                
                void ParseIndoorTrackingInfo(std::map<std::string, SdkModel::ApplicationInteriorTrackingInfo>& interiorTrackingInfoList,
                                             const rapidjson::Value& indoorTrackedBuildingsArray);
            };
        }
    }
}
