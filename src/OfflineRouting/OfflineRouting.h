// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"

#include <unordered_map>

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
                class IOfflineRoutingGraphPositioner;
                class IOfflineRoutingDataSearchService;
                class IOfflineRoutingPathFinder;
                class OfflineRoutingFeatureBuilder;
                struct OfflineRoutingFeature;
                struct OfflineRoutingGraphNode;
                struct OfflineRoutingPointOnGraph;
                struct OfflineRoutingFindPathResult;
                struct OfflineRoutingGraphBuildResults;

                typedef unsigned int OfflineRoutingFeatureId;
                typedef unsigned int OfflineRoutingGraphNodeId;

                typedef std::unordered_map<OfflineRoutingFeatureId, OfflineRoutingFeature> OfflineRoutingFeatures;
                typedef std::unordered_map<OfflineRoutingGraphNodeId, OfflineRoutingGraphNode> OfflineRoutingGraphNodes;

                typedef Eegeo::Helpers::ICallback1<const OfflineRoutingGraphBuildResults&> OfflineRoutingDataRepositoryBuildCompletedCallback;

                const float INTERIOR_FLOOR_HEIGHT = 5.0f;

                /* The line strings in geojson might not have exactly same LatLongs when connecting
                 * with another line string. This results in nodes not joining up. So if the
                 * distance between nodes is negligible then we join them together so make sure
                 * the graph is properly connected.
                 */
                const double MinimumDistanceInMeters = 0.00001;
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
