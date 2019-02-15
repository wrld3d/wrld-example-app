// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"

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
                class IOfflineRoutingDataParser
                {
                public:
                    
                    virtual ~IOfflineRoutingDataParser() {}

                    virtual bool TryParseVersions(const std::string& jsonString,
                                                  std::vector<OfflineRoutingIndoorVersion>& out_versions) = 0;

                    virtual bool TryParseFloorData(const std::string& jsonString,
                                                   std::vector<OfflineRoutingFloorData>& out_floorData) = 0;

                    virtual bool TryParseMultiFloorData(const std::string& jsonString,
                                                        std::vector<OfflineRoutingMultiFloorData>& out_multiFloorData) = 0;
                };
            }
        }
    }
}
