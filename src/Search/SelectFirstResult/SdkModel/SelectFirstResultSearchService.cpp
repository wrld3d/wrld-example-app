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
                                                                               Menu::View::IMenuModel& menuModel,
                                                                               ExampleAppMessaging::TMessageBus& messageBus)
                : m_searchQueryPerformer(searchQueryPerformer)
                , m_menuModel(menuModel)
                , m_menuItemAddedCallback(this, &SelectFirstResultSearchService::OnSearchResultAdded)
                , m_searchResultsHandler(this, &SelectFirstResultSearchService::OnSearchResultsLoaded)
                , m_messageBus(messageBus)
                , m_performingAutoSelectSearch(false)
                , m_shouldTranstion(false)
                {
                    m_menuModel.InsertItemAddedCallback(m_menuItemAddedCallback);
                    m_messageBus.SubscribeUi(m_searchResultsHandler);
                }
                
                SelectFirstResultSearchService::~SelectFirstResultSearchService()
                {
                    m_messageBus.UnsubscribeUi(m_searchResultsHandler);
                    m_menuModel.RemoveItemAddedCallback(m_menuItemAddedCallback);
                }
                
                void SelectFirstResultSearchService::PerformSearch(const std::string& queryString, const std::string& indoorMapId)
                {
                    m_performingAutoSelectSearch = true;
                    m_searchQueryPerformer.RemoveSearchQueryResults();
                    m_searchQueryPerformer.PerformSearchQuery(queryString.c_str(), false, true, indoorMapId);
                }
                
                void SelectFirstResultSearchService::OnSearchResultAdded(Menu::View::MenuItemModel& item)
                {
                    if(m_shouldTranstion && m_menuModel.GetItemCount() > 0)
                    {
                        m_menuModel.GetItemAtIndex(0).MenuOption().Select();
                    }
                    
                    m_shouldTranstion = false;
                }
                
                void SelectFirstResultSearchService::OnSearchResultsLoaded(const Search::SearchQueryResponseReceivedMessage& message)
                {
                    m_shouldTranstion = m_performingAutoSelectSearch && message.GetResults().size() > 0;
                    m_performingAutoSelectSearch = false;
                }
            }
        }
    }
}


