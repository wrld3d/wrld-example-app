// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "Types.h"
#include "OfflineRouting.h"
#include "IOfflineRoutingEngine.h"
#include "IPersistentSettingsModel.h"

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
                                         IOfflineRoutingDataBuilder& offlineRoutingDataBuilder,
                                         IOfflineRoutingFileIO& offlineRoutingFileIO,
                                         PersistentSettings::IPersistentSettingsModel& persistentSettings);

                    ~OfflineRoutingEngine() {}

                    bool TryGetLocalBuildIdForInterior(const Eegeo::Resources::Interiors::InteriorId &indoorId,
                                                       std::string &out_buildId) override;

                    bool TryLoadDataFromStorage(const Eegeo::Resources::Interiors::InteriorId &indoorId) override;

                    void LoadGraphFromNavigationData(const Eegeo::Resources::Interiors::InteriorId& indoorId,
                                                     const std::string& buildId,
                                                     const std::vector<Webservice::OfflineRoutingFloorData>& floorData,
                                                     const std::vector<Webservice::OfflineRoutingFloorPathData>& multiFloorData) override;

                private:
                    void AddFloorData(const Eegeo::Resources::Interiors::InteriorId& indoorId, const std::vector<Webservice::OfflineRoutingFloorData>& floorData);
                    void AddMultiFloorData(const Eegeo::Resources::Interiors::InteriorId& indoorId, const std::vector<Webservice::OfflineRoutingFloorPathData>& multiFloorData);

                    IOfflineRoutingDataRepository& m_offlineRoutingDataRepository;
                    IOfflineRoutingDataBuilder& m_offlineRoutingDataBuilder;
                    IOfflineRoutingFileIO& m_offlineRoutingFileIO;
                    PersistentSettings::IPersistentSettingsModel& m_persistentSettings;
                };
            }
        }
    }
}
