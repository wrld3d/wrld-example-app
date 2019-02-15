// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "InteriorId.h"
#include "OfflineRoutingFloorData.h"
#include "OfflineRoutingFloorPathData.h"

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
                struct OfflineRoutingDataRequestResponse
                {
                    OfflineRoutingWebserviceRequestId id;
                    bool succeeded;
                    Eegeo::Resources::Interiors::InteriorId interiorId;
                    std::string buildId;
                    std::vector<OfflineRoutingFloorData> floorData;
                    std::vector<OfflineRoutingFloorPathData> multiFloorData;

                    OfflineRoutingDataRequestResponse(OfflineRoutingWebserviceRequestId requestId,
                                                      bool requestSucceeded,
                                                      const Eegeo::Resources::Interiors::InteriorId& requestInteriorId,
                                                      const std::string& requestBuildId,
                                                      const std::vector<OfflineRoutingFloorData>& floorDataResults,
                                                      const std::vector<OfflineRoutingFloorPathData>& multiFloorDataResults)
                    : id(requestId)
                    , succeeded(requestSucceeded)
                    , interiorId(requestInteriorId)
                    , buildId(requestBuildId)
                    , floorData(floorDataResults)
                    , multiFloorData(multiFloorDataResults)
                    {
                    }
                };
            }
        }
    }
}
