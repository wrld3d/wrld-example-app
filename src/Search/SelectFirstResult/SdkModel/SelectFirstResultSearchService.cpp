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
                SelectFirstResultSearchService::SelectFirstResultSearchService(Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                                                                               Menu::View::IMenuModel& menuModel)
                : m_searchQueryPerformer(searchQueryPerformer)
                , m_menuModel(menuModel)
                , m_menuItemAddedCallback(this, &SelectFirstResultSearchService::OnSearchResultAdded)
                , m_didTransition(true)
                , m_deepLinkQuery("")
                {
                    m_menuModel.InsertItemAddedCallback(m_menuItemAddedCallback);
                }
                
                SelectFirstResultSearchService::~SelectFirstResultSearchService()
                {
                    m_menuModel.RemoveItemAddedCallback(m_menuItemAddedCallback);
                }
                
                void SelectFirstResultSearchService::PerformSearch(const std::string& queryString, const std::string& indoorMapId)
                {
                    m_searchQueryPerformer.RemoveSearchQueryResults();
                    m_searchQueryPerformer.PerformSearchQuery(queryString.c_str(), false, true, indoorMapId);
                    
                    m_didTransition = false;
                    m_deepLinkQuery = queryString;
                }
                
                void SelectFirstResultSearchService::OnSearchResultAdded(Menu::View::MenuItemModel& item)
                {
                    if(!m_didTransition)
                    {
                        m_didTransition = true;
                        const std::string& query = m_searchQueryPerformer.GetPreviousSearchQuery().Query();
                        if(query == m_deepLinkQuery) // This is a workaround for when the PerformSearch return no results to stop this selecting the next search they do.
                        {
                            if(m_menuModel.GetItemCount() > 0)
                            {
                                m_menuModel.GetItemAtIndex(0).MenuOption().Select();
                            }
                        }
                    }
                }
            }
        }
    }
}


