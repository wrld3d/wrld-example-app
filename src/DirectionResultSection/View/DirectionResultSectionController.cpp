// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionResultSectionController.h"


#include "SearchResultItemModel.h"

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
                //TODO:This static numbers will be replaced with vector lastAddedResults
                
                
                
                for(int i = 0; i < 4; ++i)
                {
                    m_menuOptions.RemoveItem(std::to_string(i));
                }
                
                for(int i = 0; i < 4; ++i)
                {
                    double lat = 0.0;
                    double lng = 0.0;
                    
                    std::string title = "";
                    std::string subtitle = "";
                    ExampleApp::Search::SdkModel::TagIconKey iconKey = "";

                    if(i==0)
                    {
                        lat = 56.459676;
                        lng = -2.977240;
                        title = "Westfield Valley Mall";
                        subtitle = "South Entrance";
                        iconKey = "DirectionCard_RouteStart";
                    }
                    else if(i==1)
                    {
                        lat = 56.457827;
                        lng = -2.972691;
                        title = "50 yd";
                        subtitle = "Enter Mall";
                        iconKey = "DirectionCard_EnterMallSelected";
                        
                    }
                    else if(i==2)
                    {
                        lat = 56.457860;
                        lng = -2.970793;
                        title = "40 yd";
                        subtitle = "Turn left along main concourse";
                        iconKey = "DirectionCard_StraightAhead";
                    }
                    else if(i==3)
                    {
                        lat = 56.461427;
                        lng = -2.963596;
                        title = "Turn Left";
                        subtitle = "Then 400 yd along main course";
                        iconKey = "DirectionCard_TurnLeft";
                    }
                    
                    const Eegeo::Space::LatLong& latlong = Eegeo::Space::LatLong::FromDegrees(lat, lng);
                    

                    Eegeo::Resources::Interiors::InteriorId m_buildingId("");
                    m_menuOptions.AddItem(std::to_string(i),
                                          title,
                                          subtitle,
                                          iconKey,
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


