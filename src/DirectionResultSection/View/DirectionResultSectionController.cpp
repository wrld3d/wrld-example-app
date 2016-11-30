// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WayPointModel.h"
#include "DirectionRouteModel.h"
#include "DirectionResultModel.h"
#include "SearchResultItemModel.h"
#include "DirectionResultSectionController.h"

namespace ExampleApp
{
    namespace DirectionResultSection
    {
        namespace View
        {
            
            DirectionResultSectionController::DirectionResultSectionController(Menu::View::IMenuViewModel& directionMenuViewModel
                                                                               ,Menu::View::IMenuOptionsModel& menuOptionsModel
                                                                               ,ExampleAppMessaging::TMessageBus& messageBus
                                                                               ,const Menu::View::IMenuReactionModel& menuReaction
                                                                               ,SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel)
            : m_directionMenuViewModel(directionMenuViewModel)
            , m_menuOptions(menuOptionsModel)
            , m_messageBus(messageBus)
            , m_directionResultReceivedHandler(this, &DirectionResultSectionController::OnSearchQueryResponseReceivedMessage)
            , m_directionQueryRemovedHandler(this, &DirectionResultSectionController::OnSearchQueryRemovedMessage)
            , m_menuReaction(menuReaction)
            , m_searchResultPoiViewModel(searchResultPoiViewModel)
            , m_directionsMenuStateChangedCallback(this, &DirectionResultSectionController::OnDirectionsMenuStateChanged)
            , m_wayPointCount(0)
            {
                m_messageBus.SubscribeUi(m_directionResultReceivedHandler);
                m_messageBus.SubscribeUi(m_directionsMenuStateChangedCallback);
            }
            
            DirectionResultSectionController::~DirectionResultSectionController()
            {
                m_messageBus.UnsubscribeUi(m_directionResultReceivedHandler);
                m_messageBus.UnsubscribeUi(m_directionsMenuStateChangedCallback);
            }
            
            void DirectionResultSectionController::OnSearchQueryResponseReceivedMessage(const DirectionQueryResponseReceivedMessage& message)
            {
                
                RemoveWayPoints();
                
                Direction::SdkModel::DirectionResultModel& model = message.GetDirectionResultModel();
                const std::vector<Direction::SdkModel::DirectionRouteModel>& routes = model.GetRoutes();
                if (routes.size() > 0)
                {
                    Direction::SdkModel::DirectionRouteModel routeModel = routes[0];
                    const std::vector<ExampleApp::PathDrawing::WayPointModel>& wayPointVector = routeModel.GetWayPoints();
                    const std::vector<Direction::SdkModel::DirectionInnerRouteModel>& tempVector = routeModel.GetInnerRoutes();
                    
                    Direction::SdkModel::DirectionInnerRouteModel tempInnerRouteModel = tempVector[0];
                    
                    int routeDuration = tempInnerRouteModel.GetDuration();
                    
                    Eegeo_TTY("Duration: %i",routeDuration);
                    
                    for(int i = 0; i < wayPointVector.size(); ++i)
                    {
                        ExampleApp::PathDrawing::WayPointModel wayPointModel = wayPointVector[i];
                        
                        ExampleApp::Search::SdkModel::TagIconKey iconKey = "DirectionCard_RouteStart";
                        std::string duration = "Temp Duration";
                        std::string subtitle = std::to_string(routeDuration);
                        const Eegeo::Space::LatLong latlong = wayPointModel.GetLocation();
                        
                        Eegeo::Resources::Interiors::InteriorId m_buildingId("");
                        m_menuOptions.AddItem(std::to_string(i),
                                              wayPointModel.GetTitle(),
                                              subtitle,
                                              iconKey,
                                              duration,
                                              Eegeo_NEW(SearchResultSection::View::SearchResultItemModel)("model title",
                                                                                                          latlong.ToECEF(),
                                                                                                          false,
                                                                                                          true,
                                                                                                          m_buildingId,
                                                                                                          2,
                                                                                                          m_directionMenuViewModel,                                                                           m_searchResultPoiViewModel,
                                                                                                          i,
                                                                                                          m_messageBus,
                                                                                                          m_menuReaction));
                    }
                    m_wayPointCount = wayPointVector.size();
                    
                }
                
            }
            void DirectionResultSectionController::OnSearchQueryRemovedMessage(const Search::SearchQueryRemovedMessage& message)
            {
            }
            
            void DirectionResultSectionController::OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message)
            {
                if(message.GetDirectionsMenuStage() == DirectionsMenuInitiation::Inactive)
                {
                    RemoveWayPoints();
                }
            }
            
            void DirectionResultSectionController::RemoveWayPoints()
            {
                for(int i = 0; i < m_wayPointCount; ++i)
                {
                    m_menuOptions.RemoveItem(std::to_string(i));
                }
                m_wayPointCount = 0;
            
            }

        }
    }
}


