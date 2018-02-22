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
                                                   Menu::View::IMenuModel& menuModel
                    );
                    
                    ~SelectFirstResultSearchService();
                    
                    void PerformSearch(const std::string& queryString, const std::string& indoorMapId);
                    
                private:
                    void OnSearchResultAdded(Menu::View::MenuItemModel& item);
                    
                    Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                    Eegeo::Helpers::TCallback1<SelectFirstResultSearchService, Menu::View::MenuItemModel> m_menuItemAddedCallback;
                    Menu::View::IMenuModel& m_menuModel;
                    std::string m_deepLinkQuery;
                    
                    bool m_didTransition;
                };
            }
        }
    }
}


