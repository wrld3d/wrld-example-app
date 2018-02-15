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
                                      Search::SdkModel::ISearchResultRepository& searchResultRepository,
                                      ExampleAppMessaging::TMessageBus& messageBus
                    );
                    
                    ~SelectFirstResultSearchService();
                    
                    void PerformSearch(const std::string& queryString, const std::string& indoorMapId);
                    
                private:
                    void OnSearchResultAdded(Search::SdkModel::SearchResultModel*& pSearchResultModel);
                    
                    Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                    Eegeo::Helpers::TCallback1<SelectFirstResultSearchService, Search::SdkModel::SearchResultModel*> m_searchResultAddedCallback;
                    Search::SdkModel::ISearchResultRepository& m_searchResultRepository;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    std::string m_deepLinkQuery;
                    
                    bool m_didTransition;
                };
            }
        }
    }
}


