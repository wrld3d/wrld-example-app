// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultSectionController.h"

#include <algorithm>

#include "IMenuOptionsModel.h"
#include "IAppModeModel.h"
#include "ISearchResultSectionOrder.h"
#include "SearchResultItemModel.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        namespace View
        {
            namespace
            {
                class OrderWrapper
                {
                private:
                    ISearchResultSectionOrder& m_order;
                public:
                    OrderWrapper(ISearchResultSectionOrder& order)
                        : m_order(order)
                    {
                    }
                    
                    bool operator() (const Search::SdkModel::SearchResultModel& a, const Search::SdkModel::SearchResultModel& b)
                    {
                        return m_order(a, b);
                    }
                };
                
                inline int GetOriginalIndexForSearchResult(const std::vector<Search::SdkModel::SearchResultModel>& unorderedResults, const Search::SdkModel::SearchResultModel& result)
                {
                    std::vector<Search::SdkModel::SearchResultModel>::const_iterator it = std::find(unorderedResults.begin(), unorderedResults.end(), result);
                    
                    return static_cast<int>(std::distance(unorderedResults.begin(), it));
                }
            }

            void SearchResultSectionController::OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message)
            {
                for(int i = 0; i < m_lastAddedResults.size(); ++i)
                {
                    const Search::SdkModel::SearchResultModel& model(m_lastAddedResults[i]);
                    m_menuOptions.RemoveItem(model.GetIdentifier());
                }
                
                m_lastAddedResults = message.GetResults();
                const std::vector<Search::SdkModel::SearchResultModel>& unorderedResults = message.GetResults();
                
                OrderWrapper orderWrapper(m_order);
                std::stable_sort(m_lastAddedResults.begin(), m_lastAddedResults.end(), orderWrapper);
                
                for(int i = 0; i < m_lastAddedResults.size(); ++i)
                {
                    const Search::SdkModel::SearchResultModel& model(m_lastAddedResults[i]);
                    std::string subtitle = model.GetSubtitle();
                    ExampleApp::Search::SdkModel::TagIconKey iconKey = model.GetIconKey();

                    m_menuOptions.AddItem(model.GetIdentifier(),
                                          model.GetTitle(),
                                          subtitle,
                                          iconKey,
                                          Eegeo_NEW(SearchResultItemModel)(model.GetTitle(),
                                                                           model.GetLocation().ToECEF(),
                                                                           model.IsInterior(),
                                                                           model.GetBuildingId(),
                                                                           model.GetFloor(),
                                                                           model.GetIdentifier(),
                                                                           m_searchMenuViewModel,
                                                                           m_searchResultPoiViewModel,
                                                                           GetOriginalIndexForSearchResult(unorderedResults, model),
                                                                           m_messageBus,
                                                                           m_menuReaction));
                }
            }
            
            void SearchResultSectionController::OnSearchQueryRemovedMessage(const Search::SearchQueryRemovedMessage& message)
            {
                for(int i = 0; i < m_lastAddedResults.size(); ++i)
                {
                    const Search::SdkModel::SearchResultModel& model(m_lastAddedResults[i]);
                    m_menuOptions.RemoveItem(model.GetIdentifier());
                }

                m_lastAddedResults.clear();
            }
            
            SearchResultSectionController::SearchResultSectionController(Menu::View::IMenuViewModel& searchMenuViewModel,
                                                                         Menu::View::IMenuOptionsModel& menuOptions,
                                                                         ISearchResultSectionOrder& order,
                                                                         ExampleAppMessaging::TMessageBus& messageBus,
                                                                         const Menu::View::IMenuReactionModel& menuReaction,
                                                                         SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel)
            : m_searchMenuViewModel(searchMenuViewModel)
            , m_menuOptions(menuOptions)
            , m_order(order)
            , m_messageBus(messageBus)
            , m_searchResultReceivedHandler(this, &SearchResultSectionController::OnSearchQueryResponseReceivedMessage)
            , m_searchQueryRemovedHandler(this, &SearchResultSectionController::OnSearchQueryRemovedMessage)
            , m_menuReaction(menuReaction)
            , m_searchResultPoiViewModel(searchResultPoiViewModel)
            {
                m_messageBus.SubscribeUi(m_searchResultReceivedHandler);
                m_messageBus.SubscribeUi(m_searchQueryRemovedHandler);
            }

            SearchResultSectionController::~SearchResultSectionController()
            {
                m_messageBus.UnsubscribeUi(m_searchQueryRemovedHandler);
                m_messageBus.UnsubscribeUi(m_searchResultReceivedHandler);
            }
        }
    }
}
