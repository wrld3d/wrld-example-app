// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "OfflineRouting.h"
#include "IOfflineRoutingDataParser.h"

#include <string>
#include <vector>

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
                    ~OfflineRoutingDataParser() {}

                    bool TryParseVersions(const std::string& jsonString,
                                          std::vector<OfflineRoutingIndoorVersion>& out_versions) override;

                    bool TryParseFloorData(const std::string& jsonString,
                                           std::vector<OfflineRoutingFloorData>& out_floorData) override;

                    bool TryParseMultiFloorData(const std::string& jsonString,
                                                std::vector<OfflineRoutingFloorPathData>& out_multiFloorData) override;
                };
            }
        }
    }
}
