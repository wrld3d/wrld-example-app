// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "InteriorId.h"

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
                                          const Eegeo::Resources::Interiors::InteriorId& featureIndoorId)
                    : m_id(featureId)
                    , m_type(featureType)
                    , m_name(featureName)
                    , m_indoorId(featureIndoorId)
                    {}

                    const OfflineRoutingFeatureId GetId() const { return m_id; }
                    const std::string& GetType() const { return m_type; }
                    const std::string& GetName() const { return m_name; }
                    const Eegeo::Resources::Interiors::InteriorId& GetInteriorId() const { return m_indoorId; }

                private:
                    OfflineRoutingFeatureId m_id;
                    std::string m_type;
                    std::string m_name;
                    Eegeo::Resources::Interiors::InteriorId m_indoorId;
                };
            }
        }
    }
}
