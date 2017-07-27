// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GpsMarkerModule.h"
#include "IPlatformAbstractionModule.h"
#include "GpsMarkerModel.h"
#include "GpsMarkerController.h"
#include "TerrainModelModule.h"
#include "MapModule.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            GpsMarkerModule::GpsMarkerModule(Eegeo::Location::ILocationService& locationService,
                                             Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule,
                                             Eegeo::Modules::Map::MapModule& mapModule,
                                             Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                             VisualMap::SdkModel::IVisualMapService& visualMapService,
                                             const bool createBlueSphereViews,
                                             ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pModel = Eegeo_NEW(GpsMarkerModel)(locationService, mapModule.GetBlueSphereModule().GetBlueSphereModel());

                m_pController = Eegeo_NEW(GpsMarkerController)(*m_pModel,
                                                               interiorInteractionModel,
                                                               locationService,
                                                               mapModule.GetEnvironmentFlatteningService(),
                                                               visualMapService,
                                                               mapModule.GetBlueSphereModule().GetBlueSphereView(),
                                                               mapModule.GetBlueSphereModule().GetBlueSphereAnchorView(),
                                                               createBlueSphereViews,
                                                               messageBus);
            }
            
            GpsMarkerModule::~GpsMarkerModule()
            {
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pModel;
            }
            
            IGpsMarkerController& GpsMarkerModule::GetGpsMarkerController()
            {
                return *m_pController;
            }

            GpsMarkerModel& GpsMarkerModule::GetGpsMarkerModel() const
            {
                return *m_pModel;
            }
        }
    }
}
