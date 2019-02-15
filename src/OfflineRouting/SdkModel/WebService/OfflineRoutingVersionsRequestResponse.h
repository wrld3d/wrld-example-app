// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "OfflineRoutingIndoorVersion.h"

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
                    std::vector<OfflineRoutingIndoorVersion> results;

                    OfflineRoutingVersionsRequestResponse(OfflineRoutingWebserviceRequestId requestId, bool requestSucceeded, const std::vector<OfflineRoutingIndoorVersion>& requestResults)
                    : id(requestId)
                    , succeeded(requestSucceeded)
                    , results(requestResults)
                    {
                    }
                };
            }
        }
    }
}
