// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SelectFirstResultSearchService.h"
#include "SearchQueryPerformer.h"
#include "InteriorInteractionModel.h"
#include "IMenuOption.h"
#include "SearchResultModel.h"
#include "ISearchResultRepository.h"
#include "IMenuModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SelectFirstResult
        {
            namespace SdkModel
            {
                SelectFirstResultSearchService::SelectFirstResultSearchService(Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                     Menu::View::IMenuSectionViewModel& searchSectionViewModel,
                                                     Search::SdkModel::ISearchResultRepository& searchResultRepository)
                : m_searchQueryPerformer(searchQueryPerformer)
                , m_searchResultRepository(searchResultRepository)
                , m_searchSectionViewModel(searchSectionViewModel)
                , m_searchResultAddedCallback(this, &SelectFirstResultSearchService::OnSearchResultAdded)
                , m_didTransition(true)
                {
                    m_searchResultRepository.InsertItemAddedCallback(m_searchResultAddedCallback);
                }
                
                SelectFirstResultSearchService::~SelectFirstResultSearchService()
                {
                    m_searchResultRepository.RemoveItemAddedCallback(m_searchResultAddedCallback);
                }
                
                void SelectFirstResultSearchService::HandleSearch(std::string& queryString, const std::string& interiorId)
                {
                    m_searchQueryPerformer.RemoveSearchQueryResults();
                    m_searchQueryPerformer.PerformSearchQuery(queryString.c_str(), false, true, interiorId);
                    
                    m_didTransition = false;
                }
                
                void SelectFirstResultSearchService::OnSearchResultAdded(Search::SdkModel::SearchResultModel*& pSearchResultModel)
                {
                    if(!m_didTransition)
                    {
                        if(m_searchSectionViewModel.Size() > 0)
                        {
                            m_searchSectionViewModel.GetItemAtIndex(0).MenuOption().Select();
                            m_didTransition = true;
                        }
                    }
                }
            }
        }
    }
}


