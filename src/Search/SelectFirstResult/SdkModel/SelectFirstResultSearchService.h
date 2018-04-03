// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include <vector>
#include "Search.h"
#include "ICallback.h"
#include "SearchMenu.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SelectFirstResult
        {
            namespace SdkModel
            {
                class SelectFirstResultSearchService
                {
                public:
                    
                    SelectFirstResultSearchService(Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                   Menu::View::IMenuModel& menuModel,
                                                   ExampleAppMessaging::TMessageBus& messageBus
                    );
                    
                    ~SelectFirstResultSearchService();
                    
                    void PerformSearch(const std::string& queryString, const std::string& indoorMapId);
                    
                private:
                    void OnSearchResultAdded(Menu::View::MenuItemModel& item);
                    void OnSearchResultsLoaded(const Search::SearchQueryResponseReceivedMessage& message);
                    
                    Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                    Eegeo::Helpers::TCallback1<SelectFirstResultSearchService, Menu::View::MenuItemModel> m_menuItemAddedCallback;
                    Eegeo::Helpers::TCallback1<SelectFirstResultSearchService, const Search::SearchQueryResponseReceivedMessage&> m_searchResultsHandler;
                    Menu::View::IMenuModel& m_menuModel;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    
                    bool m_performingAutoSelectSearch;
                    bool m_shouldTranstion;
                };
            }
        }
    }
}


