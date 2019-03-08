// Copyright eeGeo Ltd (2012-2019), All Rights Reserved

#pragma once

#include "OfflineRouting.h"
#include "IOfflineRoutingFileIO.h"
#include "IFileIO.h"
#include "Types.h"

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
                class OfflineRoutingFileIO : public IOfflineRoutingFileIO, private Eegeo::NonCopyable
                {
                public:
                    OfflineRoutingFileIO(Eegeo::Helpers::IFileIO& fileIO);
                    ~OfflineRoutingFileIO() {}

                    void SaveGraphToStorage(const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                            const OfflineRoutingFeatures& features,
                                            const OfflineRoutingGraphNodes& graphNodes) override;

                    bool LoadGraphFromStorage(const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                              std::vector<OfflineRoutingFeature>& out_features,
                                              std::vector<OfflineRoutingGraphNode>& out_graphNodes) override;

                private:
                    Eegeo::Helpers::IFileIO& m_fileIO;
                };
            }
        }
    }
}
