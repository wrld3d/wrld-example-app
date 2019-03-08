// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#include "OfflineRoutingEngine.h"
#include "OfflineRoutingFloorData.h"
#include "OfflineRoutingFloorPathData.h"
#include "IOfflineRoutingDataRepository.h"
#include "IOfflineRoutingDataBuilder.h"
#include "OfflineRoutingFeatureBuilder.h"
#include "IOfflineRoutingFileIO.h"
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
                namespace
                {
                    const std::string STORED_GRAPH_BUILD_ID_KEY = "Local_BuildId_For_Interior_";
                }

                OfflineRoutingEngine::OfflineRoutingEngine(IOfflineRoutingDataRepository& offlineRoutingDataRepository,
                                                           IOfflineRoutingDataBuilder& offlineRoutingDataBuilder,
                                                           IOfflineRoutingFileIO& offlineRoutingFileIO,
                                                           PersistentSettings::IPersistentSettingsModel& persistentSettings)
                : m_offlineRoutingDataRepository(offlineRoutingDataRepository)
                , m_offlineRoutingDataBuilder(offlineRoutingDataBuilder)
                , m_offlineRoutingFileIO(offlineRoutingFileIO)
                , m_persistentSettings(persistentSettings)
                {
                }

                bool OfflineRoutingEngine::TryGetLocalBuildIdForInterior(const Eegeo::Resources::Interiors::InteriorId &indoorId,
                                                                         std::string &out_buildId)
                {
                    return m_persistentSettings.TryGetValue(STORED_GRAPH_BUILD_ID_KEY + indoorId.Value(), out_buildId);
                }

                bool OfflineRoutingEngine::TryLoadDataFromStorage(const Eegeo::Resources::Interiors::InteriorId &indoorId)
                {
                    std::string buildId;
                    if (!TryGetLocalBuildIdForInterior(indoorId, buildId))
                    {
                        return false;
                    }
                    std::vector<OfflineRoutingFeature> features;
                    std::vector<OfflineRoutingGraphNode> graphNodes;
                    if (!m_offlineRoutingFileIO.LoadGraphFromStorage(indoorId, features, graphNodes))
                    {
                        return false;
                    }

                    m_offlineRoutingDataRepository.AddFeatures(features);
                    m_offlineRoutingDataRepository.AddGraphNodes(graphNodes);
                    m_offlineRoutingDataRepository.BuildGraph(true);
                    return true;
                }

                void OfflineRoutingEngine::LoadGraphFromNavigationData(const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                                                       const std::string& buildId,
                                                                       const std::vector<Webservice::OfflineRoutingFloorData>& floorData,
                                                                       const std::vector<Webservice::OfflineRoutingFloorPathData>& multiFloorData)
                {
                    AddFloorData(indoorId, floorData);
                    AddMultiFloorData(indoorId, multiFloorData);
                    m_offlineRoutingDataRepository.BuildGraph(false);
                    m_offlineRoutingFileIO.SaveGraphToStorage(indoorId, m_offlineRoutingDataRepository.GetFeatures(), m_offlineRoutingDataRepository.GetGraph());
                    m_persistentSettings.SetValue(STORED_GRAPH_BUILD_ID_KEY + indoorId.Value(), buildId);
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
                                                                                                pathData.isMultiFloor,
                                                                                                pathData.isOneWay,
                                                                                                pathData.durationMultiplier);

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
                                                                                            pathData.isMultiFloor,
                                                                                            pathData.isOneWay,
                                                                                            pathData.durationMultiplier);

                        auto graphNodes = m_offlineRoutingDataBuilder.BuildMultiFloorGraphNodes(pathData.coordinates,
                                                                                                pathData.levels,
                                                                                                featureBuilder.GetId(),
                                                                                                indoorId,
                                                                                                pathData.isOneWay);
                        featureBuilder.LinkNodes(graphNodes);

                        m_offlineRoutingDataRepository.AddGraphNodes(graphNodes);
                        m_offlineRoutingDataRepository.AddFeature(featureBuilder.Build());
                    }
                }
            }
        }
    }
}
