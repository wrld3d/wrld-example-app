// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingEngine.h"
#include "OfflineRoutingFloorData.h"
#include "OfflineRoutingFloorPathData.h"
#include "IOfflineRoutingDataRepository.h"
#include "IOfflineRoutingGraphPositioner.h"
#include "IOfflineRoutingDataBuilder.h"
#include "OfflineRoutingFeatureBuilder.h"
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

                bool OfflineRoutingEngine::TryGetLocalBuildIdForInterior(const Eegeo::Resources::Interiors::InteriorId &indoorId,
                                                                         std::string &out_buildId)
                {
                    return false; //TODO check local storage
                }

                void OfflineRoutingEngine::LoadGraphFromNavigationData(const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                                                       const std::string& buildId,
                                                                       const std::vector<Webservice::OfflineRoutingFloorData>& floorData,
                                                                       const std::vector<Webservice::OfflineRoutingFloorPathData>& multiFloorData)
                {
                    AddFloorData(indoorId, floorData);
                    AddMultiFloorData(indoorId, multiFloorData);
                    m_offlineRoutingDataRepository.BuildGraph();
                }

                void OfflineRoutingEngine::AddFloorData(const Eegeo::Resources::Interiors::InteriorId& indoorId, const std::vector<Webservice::OfflineRoutingFloorData>& floorData)
                {
                    for (const auto& data: floorData)
                    {
                        for (const auto& pathData: data.floorPaths)
                        {
                            auto featureBuilder = m_offlineRoutingDataBuilder.GetFeatureBuilder(pathData.type,
                                                                                                pathData.name,
                                                                                                indoorId,
                                                                                                false);

                            auto graphNodes = m_offlineRoutingDataBuilder.BuildGraphNodes(pathData.coordinates,
                                                                                          data.floorId,
                                                                                          featureBuilder.GetId(),
                                                                                          indoorId);
                            featureBuilder.LinkNodes(graphNodes);

                            m_offlineRoutingDataRepository.AddGraphNodes(graphNodes);
                            m_offlineRoutingDataRepository.AddFeature(featureBuilder.Build());
                        }
                    }
                }

                void OfflineRoutingEngine::AddMultiFloorData(const Eegeo::Resources::Interiors::InteriorId& indoorId, const std::vector<Webservice::OfflineRoutingFloorPathData>& multiFloorData)
                {
                    for (const auto& pathData: multiFloorData)
                    {
                        auto featureBuilder = m_offlineRoutingDataBuilder.GetFeatureBuilder(pathData.type,
                                                                                            pathData.name,
                                                                                            indoorId,
                                                                                            true);

                        auto graphNodes = m_offlineRoutingDataBuilder.BuildMultiFloorGraphNodes(pathData.coordinates,
                                                                                                pathData.levels,
                                                                                                featureBuilder.GetId(),
                                                                                                indoorId);
                        featureBuilder.LinkNodes(graphNodes);

                        m_offlineRoutingDataRepository.AddGraphNodes(graphNodes);
                        m_offlineRoutingDataRepository.AddFeature(featureBuilder.Build());
                    }
                }
            }
        }
    }
}
