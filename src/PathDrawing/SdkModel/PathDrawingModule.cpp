// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "PathDrawingModule.h"
#include "WayPointsFactory.h"
#include "WayPointsRepository.h"
#include "LatLongAltitude.h"
#include "WayPointType.h"
#include "PathDrawingController.h"

namespace ExampleApp
{
    namespace PathDrawing
    {
        namespace SdkModel
        {

            PathDrawingModule::PathDrawingModule(WorldPins::SdkModel::IWorldPinsService& worldPinsService
                                                                 , Eegeo::Routes::RouteService& routeService
                                                                 , Eegeo::EegeoWorld& eegeoWorld
                                                                 , AppCamera::SdkModel::AppGlobeCameraWrapper& cameraWrapper
                                                                 , TagSearch::ISearchResultIconKeyMapper& searchResultIconCategoryMapper
                                                                 , ExampleAppMessaging::TMessageBus& messageBus)
            
            {
                m_pWayPointsRepository = Eegeo_NEW(WayPointsRepository);

                m_pPathDrawingController = Eegeo_NEW(ExampleApp::PathDrawing::PathDrawingController)(routeService
                                                                                                     , eegeoWorld
                                                                                                     , cameraWrapper
                                                                                                     , *m_pWayPointsRepository
                                                                                                     , messageBus);
                
                m_pWayPointOnMapModel = Eegeo_NEW(ExampleApp::PathDrawing::SdkModel::WayPointOnMapModel)(worldPinsService
                                                                                                         , searchResultIconCategoryMapper
                                                                                                         , *m_pWayPointsRepository);
                            }
            
            PathDrawingModule::~PathDrawingModule()
            {                
                Eegeo_DELETE m_pWayPointsRepository;
                Eegeo_DELETE m_pPathDrawingController;
            }

            IWayPointsRepository& PathDrawingModule::GetWayPointsRepository() const
            {
                return *m_pWayPointsRepository;
            }
            
            void PathDrawingModule::Update(float dt)
            {
                m_pPathDrawingController->Update(dt);
            }
        }
    }
}
