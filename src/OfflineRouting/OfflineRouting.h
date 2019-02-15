// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            class IOfflineRoutingModule;
            class OfflineRoutingModule;

            namespace Webservice
            {
                class IOfflineRoutingDataParser;
                class OfflineRoutingDataParser;
                class IOfflineRoutingDataWebService;
                class OfflineRoutingDataWebService;
                struct OfflineRoutingIndoorVersion;
                struct OfflineRoutingFloorData;
                struct OfflineRoutingFloorPathData;
                struct OfflineRoutingMultiFloorData;
                struct OfflineRoutingVersionsRequestResponse;
                struct OfflineRoutingDataRequestResponse;

                typedef int OfflineRoutingWebserviceRequestId;
                typedef Eegeo::Helpers::ICallback1<const OfflineRoutingVersionsRequestResponse> OfflineRoutingVersionsRequestCompletedCallback;
                typedef Eegeo::Helpers::ICallback1<const OfflineRoutingDataRequestResponse> OfflineRoutingDataRequestCompletedCallback;
            }
        }
    }
}
