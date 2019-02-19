// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "Interiors.h"

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
                class IOfflineRoutingEngine
                {
                public:
                    virtual ~IOfflineRoutingEngine() {}

                    virtual bool TryGetLocalBuildIdForInterior(const Eegeo::Resources::Interiors::InteriorId &indoorId,
                                                               std::string &out_buildId) = 0;

                    virtual void LoadGraphFromNavigationData(const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                                             const std::string& buildId,
                                                             const std::vector<Webservice::OfflineRoutingFloorData>& floorData,
                                                             const std::vector<Webservice::OfflineRoutingFloorPathData>& multiFloorData) = 0;
                };
            }
        }
    }
}
