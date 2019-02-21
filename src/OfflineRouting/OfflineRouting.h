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
            class OfflineRoutingController;
            class OfflineRoutingService;

            namespace RoutingEngine
            {
                class IOfflineRoutingEngine;
                class IOfflineRoutingDataBuilder;
                class IOfflineRoutingDataRepository;
                class IOfflineRoutingDataSearchService;
                struct OfflineRoutingFeature;
                struct OfflineRoutingGraphNode;

                typedef unsigned int OfflineRoutingFeatureId;
                typedef unsigned int OfflineRoutingGraphNodeId;

                const float INTERIOR_FLOOR_HEIGHT = 5.0f;
            }

            namespace Webservice
            {
                class IOfflineRoutingDataParser;
                class OfflineRoutingDataParser;
                class IOfflineRoutingDataWebService;
                class OfflineRoutingDataWebService;
                struct OfflineRoutingIndoorVersion;
                struct OfflineRoutingFloorData;
                struct OfflineRoutingFloorPathData;
                struct OfflineRoutingVersionsRequestResponse;
                struct OfflineRoutingDataRequestResponse;

                typedef int OfflineRoutingWebserviceRequestId;
                typedef Eegeo::Helpers::ICallback1<const OfflineRoutingVersionsRequestResponse&> OfflineRoutingVersionsRequestCompletedCallback;
                typedef Eegeo::Helpers::ICallback1<const OfflineRoutingDataRequestResponse&> OfflineRoutingDataRequestCompletedCallback;
            }
        }
    }
}
