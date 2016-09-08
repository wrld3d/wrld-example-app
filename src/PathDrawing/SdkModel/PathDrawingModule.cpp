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
//            void PathDrawingModule::OnSearchQueryResponseReceivedMessage(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message)
//            {
//                WayPointsFactory *wayPointsFactory = Eegeo_NEW(ExampleApp::PathDrawing::SdkModel::WayPointsFactory)();
//
//                int pointId = 0;
//                
//                Eegeo::Space::LatLong latLongStart = Eegeo::Space::LatLong::FromDegrees(56.459676, -2.977240);
//                WayPoint* pointStart = wayPointsFactory->CreateWayPoint(++pointId
//                                                       , ExampleApp::PathDrawing::WayPointType::Start
//                                                       , latLongStart
//                                                       , "");
//                
//                Eegeo::Space::LatLong latLong1 = Eegeo::Space::LatLong::FromDegrees(56.457827, -2.972691);
//                WayPoint* point1 = wayPointsFactory->CreateWayPoint(++pointId
//                                                                    , ExampleApp::PathDrawing::WayPointType::CheckPoint
//                                                                    , latLong1
//                                                                    , "");
//                
//                Eegeo::Space::LatLong latLong2 = Eegeo::Space::LatLong::FromDegrees(56.457860, -2.970793);
//                WayPoint* point2 = wayPointsFactory->CreateWayPoint(++pointId
//                                                                    , ExampleApp::PathDrawing::WayPointType::CheckPoint
//                                                                    , latLong2
//                                                                    , "");
//                
//                Eegeo::Space::LatLong latLong3 = Eegeo::Space::LatLong::FromDegrees(56.461427, -2.963596);
//                WayPoint* point3 = wayPointsFactory->CreateWayPoint(++pointId
//                                                                    , ExampleApp::PathDrawing::WayPointType::CheckPoint
//                                                                    , latLong3
//                                                                    , "");
//                
//                Eegeo::Space::LatLong latLongEnd = Eegeo::Space::LatLong::FromDegrees(56.460882, -2.962729);
//                WayPoint* pointEnd = wayPointsFactory->CreateWayPoint(++pointId
//                                                       , ExampleApp::PathDrawing::WayPointType::End
//                                                       , latLongEnd
//                                                       , "");
//                
//                m_pWayPointsRepository->AddItem(pointStart);
//                m_pWayPointsRepository->AddItem(point1);
//                m_pWayPointsRepository->AddItem(point2);
//                m_pWayPointsRepository->AddItem(point3);
//                m_pWayPointsRepository->AddItem(pointEnd);
//
//            }

            PathDrawingModule::PathDrawingModule(WorldPins::SdkModel::IWorldPinsService& worldPinsService
                                                 , Eegeo::Routes::RouteService& routeService
                                                 , Eegeo::EegeoWorld& eegeoWorld
                                                 , AppCamera::SdkModel::AppGlobeCameraWrapper& cameraWrapper
                                                 , CategorySearch::ISearchResultIconCategoryMapper& searchResultIconCategoryMapper
                                                 , ExampleAppMessaging::TMessageBus& messageBus)
//            : m_searchResultReceivedHandler(this, &PathDrawingModule::OnSearchQueryResponseReceivedMessage)
            
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
                
//                m_messageBus.SubscribeUi(m_searchResultReceivedHandler);
            }
            
            PathDrawingModule::~PathDrawingModule()
            {
//                m_messageBus.UnsubscribeUi(m_searchResultReceivedHandler);
                
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
