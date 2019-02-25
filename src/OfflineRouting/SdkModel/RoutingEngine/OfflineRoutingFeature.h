// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "InteriorId.h"
#include "Point3Spline.h"

#include <string>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                struct OfflineRoutingFeature
                {
                    OfflineRoutingFeature()
                    {}

                    OfflineRoutingFeature(const OfflineRoutingFeatureId featureId,
                                          const std::string& featureType,
                                          const std::string& featureName,
                                          const Eegeo::Resources::Interiors::InteriorId& featureIndoorId,
                                          bool isMultiFloor,
                                          std::vector<OfflineRoutingGraphNodeId> featureNodes,
                                          Eegeo::Geometry::Point3Spline featureSpline)
                    : m_id(featureId)
                    , m_type(featureType)
                    , m_name(featureName)
                    , m_indoorId(featureIndoorId)
                    , m_isMultiFloor(isMultiFloor)
                    , m_featureNodes(featureNodes)
                    , m_featureSpline(featureSpline)
                    {}

                    const OfflineRoutingFeatureId GetId() const { return m_id; }
                    const std::string& GetType() const { return m_type; }
                    const std::string& GetName() const { return m_name; }
                    const Eegeo::Resources::Interiors::InteriorId& GetInteriorId() const { return m_indoorId; }
                    const bool GetIsMultiFloor() const { return m_isMultiFloor; }
                    const std::vector<OfflineRoutingGraphNodeId>& GetLinkedNodes() const { return m_featureNodes; }
                    const Eegeo::Geometry::Point3Spline& GetSpline() const { return m_featureSpline; }

                private:
                    OfflineRoutingFeatureId m_id;
                    std::string m_type;
                    std::string m_name;
                    Eegeo::Resources::Interiors::InteriorId m_indoorId;
                    bool m_isMultiFloor;
                    std::vector<OfflineRoutingGraphNodeId> m_featureNodes;
                    Eegeo::Geometry::Point3Spline m_featureSpline;
                };
            }
        }
    }
}
