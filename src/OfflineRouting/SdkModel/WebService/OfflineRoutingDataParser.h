// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "document.h"
#include "OfflineRouting.h"
#include "IOfflineRoutingDataParser.h"
#include "OfflineRoutingIndoorVersion.h"
#include "OfflineRoutingFloorData.h"
#include "OfflineRoutingMultiFloorData.h"

#include <functional>

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
                                          std::vector<OfflineRoutingIndoorVersion>& out_versions);

                    bool TryParseFloorData(const std::string& jsonString,
                                           std::vector<OfflineRoutingFloorData>& out_floorData);

                    bool TryParseMultiFloorData(const std::string& jsonString,
                                                std::vector<OfflineRoutingMultiFloorData>& out_multiFloorData);
                };
            }
        }
    }
}
