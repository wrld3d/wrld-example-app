// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GpsMarkerModule.h"
#include "IPlatformAbstractionModule.h"
#include "GpsMarkerModel.h"
#include "GpsMarkerController.h"
#include "TerrainModelModule.h"
#include "MapModule.h"
#include "AccuracyRingRenderableFactory.h"
#include "AccuracyRingRenderable.h"
#include "AccuracyRingView.h"
#include "RenderingModule.h"
#include "VectorMath.h"
#include "RenderableFilters.h"

namespace ExampleApp
{
    namespace GpsMarker
    {
        namespace SdkModel
        {
            GpsMarkerModule::GpsMarkerModule(Eegeo::Location::ILocationService& locationService,
                                             Eegeo::Modules::Map::Layers::TerrainModelModule& terrainModelModule,
                                             Eegeo::Modules::Map::MapModule& mapModule,
                                             Eegeo::Modules::Core::RenderingModule& renderingModule,
                                             Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                             VisualMap::SdkModel::IVisualMapService& visualMapService,
                                             const bool createBlueSphereViews,
                                             ExampleAppMessaging::TMessageBus& messageBus)
            : m_renderableFilters(renderingModule.GetRenderableFilters())
            {
                m_pModel = Eegeo_NEW(GpsMarkerModel)(locationService, interiorInteractionModel, mapModule.GetBlueSphereModule().GetBlueSphereModel());

                m_pRingRenderableFactory = AccuracyRingRenderableFactory::Create(renderingModule);
                m_pRingRenderable = m_pRingRenderableFactory->BuildRenderable();
                m_pRingRenderable->SetColors(Eegeo::v4(18.0f/255.0f, 86.0f/255.0f, 172.0f/255.0f, 0.75f),
                                             Eegeo::v4(18.0f/255.0f, 86.0f/255.0f, 172.0f/255.0f, 0.8f));
                m_pRingView = Eegeo_NEW(AccuracyRingView)(*m_pRingRenderable);

                m_renderableFilters.AddRenderableFilter(*m_pRingView);

                m_pController = Eegeo_NEW(GpsMarkerController)(*m_pModel,
                                                               interiorInteractionModel,
                                                               locationService,
                                                               mapModule.GetEnvironmentFlatteningService(),
                                                               visualMapService,
                                                               mapModule.GetBlueSphereModule().GetBlueSphereView(),
                                                               mapModule.GetBlueSphereModule().GetBlueSphereAnchorView(),
                                                               createBlueSphereViews,
                                                               *m_pRingView,
                                                               messageBus);
            }
            
            GpsMarkerModule::~GpsMarkerModule()
            {
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pModel;

                m_renderableFilters.RemoveRenderableFilter(*m_pRingView);

                Eegeo_DELETE m_pRingView;
                Eegeo_DELETE m_pRingRenderable;
                Eegeo_DELETE m_pRingRenderableFactory;
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
