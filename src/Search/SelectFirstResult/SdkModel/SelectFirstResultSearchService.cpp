// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SelectFirstResultSearchService.h"
#include "SearchQueryPerformer.h"
#include "IMenuOption.h"
#include "ISearchResultRepository.h"
#include "IMenuModel.h"
#include "SearchResultItemModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SelectFirstResult
        {
            namespace SdkModel
            {
                SelectFirstResultSearchService::SelectFirstResultSearchService(Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer)
                : m_searchQueryPerformer(searchQueryPerformer)
                {
                }
                
                void SelectFirstResultSearchService::PerformSearch(const std::string& queryString, const std::string& indoorMapId)
                {
                    m_searchQueryPerformer.RemoveSearchQueryResults();
                    bool selectFirstResult = true;
                    m_searchQueryPerformer.AskForSearchQuery(queryString, selectFirstResult, indoorMapId);
                }
            }
        }
    }
}


