// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "Interiors.h"
#include "LatLongAltitude.h"

#include <string>
#include <vector>

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                class IOfflineRoutingDataBuilder
                {
                public:
                    virtual ~IOfflineRoutingDataBuilder() {}

                    virtual std::vector<OfflineRoutingGraphNode> BuildGraphNodes(const std::vector<Eegeo::Space::LatLong>& coordinates,
                                                                                 int floorId,
                                                                                 const OfflineRoutingFeatureId& featureId,
                                                                                 const Eegeo::Resources::Interiors::InteriorId& indoorId) = 0;

                    virtual OfflineRoutingFeature BuildFeature(const std::string& type,
                                                               const std::string& name,
                                                               int floorId,
                                                               const Eegeo::Resources::Interiors::InteriorId& indoorId) = 0;
                };
            }
        }
    }
}
