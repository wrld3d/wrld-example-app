// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "OfflineRouting.h"
#include "IOfflineRoutingEngine.h"

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
                class OfflineRoutingEngine : public IOfflineRoutingEngine, private Eegeo::NonCopyable
                {
                public:
                    OfflineRoutingEngine(IOfflineRoutingDataRepository& offlineRoutingDataRepository,
                                         IOfflineRoutingDataBuilder& offlineRoutingDataBuilder);

                    ~OfflineRoutingEngine() {}

                    bool TryGetLatestBuildIdForInterior(const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                                        std::string& out_buildId) override;

                    void LoadGraphFromNavigationData(const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                                     const std::string& buildId,
                                                     const std::vector<Webservice::OfflineRoutingFloorData>& floorData,
                                                     const std::vector<Webservice::OfflineRoutingFloorPathData>& multiFloorData) override;

                private:
                    IOfflineRoutingDataRepository& m_offlineRoutingDataRepository;
                    IOfflineRoutingDataBuilder& m_offlineRoutingDataBuilder;
                };
            }
        }
    }
}
