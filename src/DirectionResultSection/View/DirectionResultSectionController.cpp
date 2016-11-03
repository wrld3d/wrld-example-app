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
                
                for(int i = 0; i < 2; ++i)
                {
                    m_menuOptions.RemoveItem(std::to_string(i));
                }
                
                Direction::SdkModel::DirectionResultModel& model = message.GetDirectionResultModel();
                const std::vector<Direction::SdkModel::DirectionRouteModel>& routes = model.GetRoutes();
                if (routes.size() > 0)
                {
                    Direction::SdkModel::DirectionRouteModel routeModel = routes[0];
                    const std::vector<ExampleApp::PathDrawing::WayPointModel>& wayPointVector = routeModel.GetWayPoints();
                    for(int i = 0; i < wayPointVector.size(); ++i)
                    {
                        ExampleApp::PathDrawing::WayPointModel wayPointModel = wayPointVector[i];

                        
                        std::string subtitle = "";
                        ExampleApp::Search::SdkModel::TagIconKey iconKey = "";
                        std::string duration = "Temp Duration";
                        if(i%4 == 0)
                        {

                            subtitle = "South Entrance";
                            iconKey = "DirectionCard_RouteStart";
                        }
                        else if(i%4 == 1)
                        {

                            subtitle = "Enter Mall";
                            iconKey = "DirectionCard_EnterMallSelected";
                            
                        }
                        else if(i%4 == 2)
                        {

                            subtitle = "Turn left along main concourse";
                            iconKey = "DirectionCard_StraightAhead";
                        }
                        else if(i%4 == 3)
                        {

                            subtitle = "Then 400 yd along main course";
                            iconKey = "DirectionCard_TurnLeft";
                        }
                        
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
                    

                }
                
            }
            void DirectionResultSectionController::OnSearchQueryRemovedMessage(const Search::SearchQueryRemovedMessage& message)
            {
            }
            
            void DirectionResultSectionController::OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message)
            {
                if(message.GetDirectionsMenuStage() == DirectionsMenuInitiation::Inactive)
                {
                    for(int i = 0; i < 4; ++i)
                    {
                        m_menuOptions.RemoveItem(std::to_string(i));
                    }
                }
            }
        }
    }
}


