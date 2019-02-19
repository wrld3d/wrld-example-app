// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingEngine.h"
#include "OfflineRoutingFloorData.h"
#include "OfflineRoutingFloorPathData.h"
#include "IOfflineRoutingDataRepository.h"
#include "IOfflineRoutingDataBuilder.h"
#include "OfflineRoutingFeature.h"
#include "OfflineRoutingGraphNode.h"

namespace ExampleApp
{
    namespace OfflineRouting
    {
        namespace SdkModel
        {
            namespace RoutingEngine
            {
                OfflineRoutingEngine::OfflineRoutingEngine(IOfflineRoutingDataRepository& offlineRoutingDataRepository,
                                                           IOfflineRoutingDataBuilder& offlineRoutingDataBuilder)
                : m_offlineRoutingDataRepository(offlineRoutingDataRepository)
                , m_offlineRoutingDataBuilder(offlineRoutingDataBuilder)
                {
                }

                bool OfflineRoutingEngine::TryGetLatestBuildIdForInterior(const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                                                          std::string& out_buildId)
                {
                    return false; //TODO check local storage
                }

                void OfflineRoutingEngine::LoadGraphFromNavigationData(const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                                                       const std::string& buildId,
                                                                       const std::vector<Webservice::OfflineRoutingFloorData>& floorData,
                                                                       const std::vector<Webservice::OfflineRoutingFloorPathData>& multiFloorData)
                {
                    for (const auto& data: floorData)
                    {
                        for (const auto& pathData: data.floorPaths)
                        {
                            OfflineRoutingFeature feature = m_offlineRoutingDataBuilder.BuildFeature(pathData.type,
                                                                                                     pathData.name,
                                                                                                     data.floorId,
                                                                                                     indoorId);
                            m_offlineRoutingDataRepository.AddFeature(feature);

                            std::vector<OfflineRoutingGraphNode> graphNodes = m_offlineRoutingDataBuilder.BuildGraphNodes(pathData.coordinates,
                                                                                                                          data.floorId,
                                                                                                                          feature.id,
                                                                                                                          indoorId);
                            for (const auto& node: graphNodes)
                            {
                                m_offlineRoutingDataRepository.AddGraphNode(node);
                            }
                        }
                    }
                }
            }
        }
    }
}
