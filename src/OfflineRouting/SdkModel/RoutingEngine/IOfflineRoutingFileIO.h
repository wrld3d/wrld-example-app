// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "InteriorId.h"

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
                class IOfflineRoutingFileIO
                {
                public:
                    virtual ~IOfflineRoutingFileIO() {}

                    virtual void SaveGraphToStorage(const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                    const OfflineRoutingFeatures& features,
                                                    const OfflineRoutingGraphNodes& graphNodes) = 0;

                    virtual bool LoadGraphFromStorage(const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                      std::vector<OfflineRoutingFeature>& out_features,
                                                      std::vector<OfflineRoutingGraphNode>& out_graphNodes) = 0;
                };
            }
        }
    }
}
