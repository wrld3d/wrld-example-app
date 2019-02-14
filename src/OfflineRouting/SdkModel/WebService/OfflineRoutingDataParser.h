// Copyright eeGeo Ltd (2012-2018), All Rights Reserved

#pragma once

#include "Types.h"
#include "OfflineRouting.h"
#include "IOfflineRoutingDataParser.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace Webservice
            {
                class OfflineRoutingDataParser : public IOfflineRoutingDataParser, private Eegeo::NonCopyable
                {
                public:
                    OfflineRoutingDataParser();
                    
                    ~OfflineRoutingDataParser() {}

                    bool TryParseVersions(const std::string& jsonString,
                                          std::vector<OfflineRoutingIndoorVersion>& result);
                };
            }
        }
    }
}
