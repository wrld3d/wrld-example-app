// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "IMenuViewModel.h"
#include "SearchQueryPerformedMessage.h"
#include "SearchQueryResponseReceivedMessage.h"
#include "SearchResultModel.h"
#include "IMenuReactionModel.h"
#include "SearchResultPoi.h"
#include "IMenuOptionsModel.h"
#include "ISearchResultPoiViewModel.h"
#include "DirectionMenuFindDirectionMessage.h"
#include "DirectionQueryResponseReceivedMessage.h"
#include "DirectionsMenuStateChangedMessage.h"

namespace ExampleApp
{
    namespace DirectionResultSection
    {
        namespace View
        {
            class DirectionResultSectionController
            {
            
            private:
                Menu::View::IMenuViewModel& m_directionMenuViewModel;
                Menu::View::IMenuOptionsModel& m_menuOptions;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                std::vector<Search::SdkModel::SearchResultModel> m_lastAddedResults;
                const Menu::View::IMenuReactionModel& m_menuReaction;
                SearchResultPoi::View::ISearchResultPoiViewModel& m_searchResultPoiViewModel;
                
                Eegeo::Helpers::TCallback1<DirectionResultSectionController, const DirectionQueryResponseReceivedMessage&> m_directionResultReceivedHandler;
                Eegeo::Helpers::TCallback1<DirectionResultSectionController, const Search::SearchQueryRemovedMessage&> m_directionQueryRemovedHandler;
                
                void OnSearchQueryResponseReceivedMessage(const DirectionQueryResponseReceivedMessage& message);
                void OnSearchQueryRemovedMessage(const Search::SearchQueryRemovedMessage& message);
                Eegeo::Helpers::TCallback1<DirectionResultSectionController, const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage&> m_directionsMenuStateChangedCallback;
                
                void OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message);
                
            public:
                DirectionResultSectionController(Menu::View::IMenuViewModel& directionMenuViewModel,
                                              Menu::View::IMenuOptionsModel& menuOptionsModel,
                                              ExampleAppMessaging::TMessageBus& messageBus,
                                              const Menu::View::IMenuReactionModel& menuReaction,
                                              SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel);
                
                ~DirectionResultSectionController();
            };
        }
    }
}