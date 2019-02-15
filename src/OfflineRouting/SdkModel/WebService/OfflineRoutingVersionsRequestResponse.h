// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "OfflineRoutingIndoorVersion.h"
#include "InteriorId.h"

#include <vector>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace Webservice
            {
                struct OfflineRoutingVersionsRequestResponse
                {
                    OfflineRoutingWebserviceRequestId id;
                    bool succeeded;
                    Eegeo::Resources::Interiors::InteriorId interiorId;
                    std::vector<OfflineRoutingIndoorVersion> results;

                    OfflineRoutingVersionsRequestResponse(OfflineRoutingWebserviceRequestId requestId,
                                                          bool requestSucceeded,
                                                          const Eegeo::Resources::Interiors::InteriorId& requestInteriorId,
                                                          const std::vector<OfflineRoutingIndoorVersion>& requestResults)
                    : id(requestId)
                    , succeeded(requestSucceeded)
                    , interiorId(requestInteriorId)
                    , results(requestResults)
                    {
                    }
                };
            }
        }
    }
}
