// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <string>
#include <vector>
#include "Search.h"
#include "ICallback.h"
#include "SearchMenu.h"

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
                                      Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                                      Search::SdkModel::ISearchResultRepository& searchResultRepository);
                    
                    ~SelectFirstResultSearchService();
                    
                    void HandleSearch(std::string& queryString, const std::string& interiorId = "");
                    
                private:
                    void OnSearchResultAdded(Search::SdkModel::SearchResultModel*& pSearchResultModel);
                    
                    Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                    Menu::View::IMenuSectionViewModel& m_searchSectionViewModel;
                    Eegeo::Helpers::TCallback1<SelectFirstResultSearchService, Search::SdkModel::SearchResultModel*> m_searchResultAddedCallback;
                    Search::SdkModel::ISearchResultRepository& m_searchResultRepository;
                    
                    bool m_didTransition;
                };
            }
        }
    }
}


