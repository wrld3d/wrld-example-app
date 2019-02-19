// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingDataRepository.h"
#include "OfflineRoutingGraphNode.h"
#include "OfflineRoutingFeature.h"
#include "InteriorId.h"
#include "Types.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                OfflineRoutingDataRepository::OfflineRoutingDataRepository()
                {}

                void OfflineRoutingDataRepository::AddGraphNode(const OfflineRoutingGraphNode& node)
                {
                    Eegeo_ASSERT(!(HasGraphNode(node.id)), "Already have data for node %d", node.id);

                    m_interiorGraphNodes[node.id] = node;
                }

                void OfflineRoutingDataRepository::AddFeature(const OfflineRoutingFeature& feature)
                {
                    Eegeo_ASSERT(!(HasFeature(feature.id)), "Already have data for feature %d", feature.id);

                    m_interiorFeatures[feature.id] = feature;
                }

                bool OfflineRoutingDataRepository::HasGraphNode(const OfflineRoutingGraphNodeId& id) const
                {
                    return m_interiorGraphNodes.find(id) != m_interiorGraphNodes.end();
                }

                bool OfflineRoutingDataRepository::HasFeature(const OfflineRoutingFeatureId& id) const
                {
                    return m_interiorFeatures.find(id) != m_interiorFeatures.end();
                }

                const OfflineRoutingGraphNode& OfflineRoutingDataRepository::GetGraphNode(const OfflineRoutingGraphNodeId& id) const
                {
                    Eegeo_ASSERT((HasGraphNode(id)), "Does not have data for node %d", id);
                    return m_interiorGraphNodes.at(id);
                }

                const OfflineRoutingFeature& OfflineRoutingDataRepository::GetFeature(const OfflineRoutingFeatureId& id) const
                {
                    Eegeo_ASSERT((HasFeature(id)), "Does not have data for feature %d", id);
                    return m_interiorFeatures.at(id);
                }
            }
        }
    }
}
