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
                    OfflineRoutingFeatureId id;
                    std::string type;
                    std::string name;
                    int floorId;
                    Eegeo::Resources::Interiors::InteriorId indoorId;

                    OfflineRoutingFeature()
                    {}

                    OfflineRoutingFeature(const OfflineRoutingFeatureId featureId,
                                          const std::string& featureType,
                                          const std::string& featureName,
                                          const int featureFloorId,
                                          const Eegeo::Resources::Interiors::InteriorId& featureIndoorId)
                    : id(featureId)
                    , type(featureType)
                    , name(featureName)
                    , floorId(featureFloorId)
                    , indoorId(featureIndoorId)
                    {}
                };
            }
        }
    }
}
