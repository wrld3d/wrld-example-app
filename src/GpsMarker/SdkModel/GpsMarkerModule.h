// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IGpsMarkerModule.h"
#include "GpsMarker.h"
#include "Modules.h"
#include "Location.h"
#include "BidirectionalBus.h"
#include "VisualMapService.h"
#include "BlueSphere.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            class GpsMarkerModule : public IGpsMarkerModule
            {
            public:
                
                GpsMarkerModule(Eegeo::Location::ILocationService& locationService,
                                Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule,
                                Eegeo::Modules::Map::MapModule& mapModule,
                                Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                VisualMap::SdkModel::IVisualMapService& visualMapService,
                                const bool createBlueSphereViews,
                                ExampleAppMessaging::TMessageBus& messageBus);
                ~GpsMarkerModule();
                
                IGpsMarkerController& GetGpsMarkerController();

                GpsMarkerModel& GetGpsMarkerModel() const;
                
            private:
                
                GpsMarkerModel* m_pModel;
                IGpsMarkerController* m_pController;
            };
        }
    }
}
