// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuController.h"

#include <algorithm>

#include "IAppModeModel.h"
#include "ISearchResultMenuOrder.h"
#include "SearchResultItemModel.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            namespace
            {
                class OrderWrapper
                {
                private:
                    ISearchResultMenuOrder& m_order;
                public:
                    OrderWrapper(ISearchResultMenuOrder& order)
                        : m_order(order)
                    {
                    }
                    
                    bool operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b)
                    {
                        return m_order(a, b);
                    }
                };
            }
            
            void SearchResultMenuController::OnSearchQueryPerformedMessage(const Search::SearchQueryPerformedMessage& message)
            {
                m_searchMenuViewModel.Close();
            }

            void SearchResultMenuController::OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message)
            {
                // TODO: set search box text using headerString
                std::string headerString = CategorySearch::View::GetPresentationStringForQuery(m_categorySearchRepository, message.GetQuery());
                
                for(int i = 0; i < m_lastAddedResults.size(); ++i)
                {
                    const Search::SdkModel::SearchResultModel& model(m_lastAddedResults[i]);
                    m_menuOptions.RemoveItem(model.GetIdentifier());
                }
                
                m_lastAddedResults = message.GetResults();
                OrderWrapper orderWrapper(m_order);
                std::stable_sort(m_lastAddedResults.begin(), m_lastAddedResults.end(), orderWrapper);
                
                for(int i = 0; i < m_lastAddedResults.size(); ++i)
                {
                    const Search::SdkModel::SearchResultModel& model(m_lastAddedResults[i]);
                    m_menuOptions.AddItem(model.GetIdentifier(),
                                          model.GetTitle(),
                                          model.GetSubtitle(),
                                          model.GetCategory(),
                                          Eegeo_NEW(SearchResultItemModel)(model.GetTitle(),
                                                                           model.GetLocation().ToECEF(),
                                                                           model.IsInterior(),
                                                                           model.GetBuildingId(),
                                                                           model.GetFloor(),
                                                                           m_searchMenuViewModel,
                                                                           m_messageBus));
                }
            }

            SearchResultMenuController::SearchResultMenuController(Menu::View::IMenuViewModel& searchMenuViewModel,
                                                                   Menu::View::IMenuOptionsModel& menuOptions,
                                                                   ISearchResultMenuOrder& order,
                                                                   CategorySearch::View::ICategorySearchRepository& categorySearchRepository,
                                                                   ExampleAppMessaging::TMessageBus& messageBus)
            : m_searchMenuViewModel(searchMenuViewModel)
            , m_menuOptions(menuOptions)
            , m_order(order)
            , m_categorySearchRepository(categorySearchRepository)
            , m_messageBus(messageBus)
            , m_searchQueryIssuedHandler(this, &SearchResultMenuController::OnSearchQueryPerformedMessage)
            , m_searchResultReceivedHandler(this, &SearchResultMenuController::OnSearchQueryResponseReceivedMessage)
            {
                m_messageBus.SubscribeUi(m_searchQueryIssuedHandler);
                m_messageBus.SubscribeUi(m_searchResultReceivedHandler);
            }

            SearchResultMenuController::~SearchResultMenuController()
            {
                m_messageBus.UnsubscribeUi(m_searchResultReceivedHandler);
                m_messageBus.UnsubscribeUi(m_searchQueryIssuedHandler);
            }
        }
    }
}
