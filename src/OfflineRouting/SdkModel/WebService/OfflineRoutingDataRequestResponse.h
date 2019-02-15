// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"

#include <vector>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace Webservice
            {
                struct OfflineRoutingDataRequestResponse
                {
                    OfflineRoutingWebserviceRequestId id;
                    bool succeeded;
                    std::vector<OfflineRoutingFloorData> floorData;
                    std::vector<OfflineRoutingMultiFloorData> multiFloorData;

                    OfflineRoutingDataRequestResponse(OfflineRoutingWebserviceRequestId requestId,
                                                      bool requestSucceeded,
                                                      const std::vector<OfflineRoutingFloorData>& floorDataResults,
                                                      const std::vector<OfflineRoutingMultiFloorData>& multiFloorDataResults)
                    : id(requestId)
                    , succeeded(requestSucceeded)
                    , floorData(floorDataResults)
                    , multiFloorData(multiFloorDataResults)
                    {
                    }
                };
            }
        }
    }
}
