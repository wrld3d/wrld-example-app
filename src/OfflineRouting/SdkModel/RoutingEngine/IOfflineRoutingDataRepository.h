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
            namespace RoutingEngine
            {
                class IOfflineRoutingDataRepository
                {
                public:
                    virtual ~IOfflineRoutingDataRepository() {}

                    virtual void AddGraphNode(const OfflineRoutingGraphNode& node) = 0;
                    virtual void AddGraphNodes(const std::vector<OfflineRoutingGraphNode>& nodes) = 0;
                    virtual void AddFeature(const OfflineRoutingFeature& feature) = 0;
                    virtual void AddFeatures(const std::vector<OfflineRoutingFeature>& features) = 0;

                    virtual bool HasGraphNode(const OfflineRoutingGraphNodeId& id) const = 0;
                    virtual bool HasFeature(const OfflineRoutingFeatureId& id) const = 0;

                    virtual const OfflineRoutingGraphNode& GetGraphNode(const OfflineRoutingGraphNodeId& id) const = 0;
                    virtual const OfflineRoutingFeature& GetFeature(const OfflineRoutingFeatureId& id) const = 0;

                    virtual const OfflineRoutingGraphNodes& GetGraph() const = 0;
                    virtual const OfflineRoutingFeatures& GetFeatures() const = 0;

                    virtual void BuildGraph(bool featureNodesAlreadyLinked) = 0;

                    virtual void RegisterGraphBuiltCallback(OfflineRoutingDataRepositoryBuildCompletedCallback& callback) = 0;
                    virtual void UnregisterGraphBuiltCallback(OfflineRoutingDataRepositoryBuildCompletedCallback& callback) = 0;
                };
            }
        }
    }
}
