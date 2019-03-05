// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingFeatureBuilder.h"
#include "OfflineRoutingGraphNode.h"
#include "OfflineRoutingFeature.h"
#include "Point3Spline.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                OfflineRoutingFeatureBuilder::OfflineRoutingFeatureBuilder(const OfflineRoutingFeatureId featureId,
                                                                           const std::string& featureType,
                                                                           const std::string& featureName,
                                                                           const Eegeo::Resources::Interiors::InteriorId& featureIndoorId,
                                                                           bool isMultiFloor,
                                                                           bool isOneWay,
                                                                           int durationMultiplier)
                : m_id(featureId)
                , m_type(featureType)
                , m_name(featureName)
                , m_indoorId(featureIndoorId)
                , m_isMultiFloor(isMultiFloor)
                , m_isOneWay(isOneWay)
                , m_durationMultiplier(durationMultiplier)
                {}

                const OfflineRoutingFeatureId OfflineRoutingFeatureBuilder::GetId() const
                {
                    return m_id;
                }

                OfflineRoutingFeatureBuilder& OfflineRoutingFeatureBuilder::LinkNodes(const std::vector<OfflineRoutingGraphNode>& graphNodes)
                {
                    m_featureNodes.reserve(graphNodes.size());
                    m_featureSplinePoints.reserve(graphNodes.size());

                    for (const OfflineRoutingGraphNode& node : graphNodes)
                    {
                        m_featureNodes.emplace_back(node.GetId());
                        m_featureSplinePoints.emplace_back(node.GetPoint().ToSingle());
                    }

                    return *this;
                }

                OfflineRoutingFeature OfflineRoutingFeatureBuilder::Build()
                {
                    return OfflineRoutingFeature(m_id,
                                                 m_type,
                                                 m_name,
                                                 m_indoorId,
                                                 m_isMultiFloor,
                                                 m_featureNodes,
                                                 Eegeo::Geometry::Point3Spline::BuildFromPoints(m_featureSplinePoints),
                                                 m_isOneWay,
                                                 m_durationMultiplier);
                }
            }
        }
    }
}
