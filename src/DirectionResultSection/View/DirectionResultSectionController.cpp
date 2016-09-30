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
                    
                    if(i==0)
                    {
                        lat = 56.459676;
                        lng = -2.977240;
                    }
                    else if(i==1)
                    {
                        lat = 56.457827;
                        lng = -2.972691;
                    }
                    else if(i==2)
                    {
                        lat = 56.457860;
                        lng = -2.970793;
                    }
                    else if(i==3)
                    {
                        lat = 56.461427;
                        lng = -2.963596;
                    }
                    
                    const Eegeo::Space::LatLong& latlong = Eegeo::Space::LatLong::FromDegrees(lat, lng);
                    
                    std::string subtitle = "sub";
                    ExampleApp::Search::SdkModel::TagIconKey iconKey1 = "default";
                    Eegeo::Resources::Interiors::InteriorId m_buildingId("");
                    m_menuOptions.AddItem(std::to_string(i),
                                          "title",
                                          subtitle,
                                          iconKey1,
                                          Eegeo_NEW(SearchResultSection::View::SearchResultItemModel)("model title",
                                                                           latlong.ToECEF(),
                                                                           false,
                                                                           m_buildingId,
                                                                           2,
                                                                           m_directionMenuViewModel,
                                                                           m_searchResultPoiViewModel,
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


