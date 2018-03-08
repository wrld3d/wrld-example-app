// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchWidgetController.h"
#include "SearchResultSectionItemSelectedMessage.h"
#include "SearchServicesResult.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchWidgetController::SearchWidgetController(ISearchWidgetView& view,
                                                           ExampleAppMessaging::TMessageBus& messageBus,
                                                           SearchServices& searchServices)
            : m_view(view)
            , m_messageBus(messageBus)
            , m_searchServices(searchServices)
            , m_onSearchResultsClearedCallback(this, &SearchWidgetController::OnSearchResultsCleared)
            , m_onSearchResultSelectedCallback(this, &SearchWidgetController::OnSearchResultSelected)
            , m_onSearchQueryRefreshedHandler(this, &SearchWidgetController::OnSearchQueryRefreshedMessage)
            {
                m_view.InsertSearchClearedCallback(m_onSearchResultsClearedCallback);
				m_view.InsertResultSelectedCallback(m_onSearchResultSelectedCallback);

                m_messageBus.SubscribeUi(m_onSearchQueryRefreshedHandler);
            }

            SearchWidgetController::~SearchWidgetController()
            {
                m_messageBus.UnsubscribeUi(m_onSearchQueryRefreshedHandler);

				m_view.RemoveResultSelectedCallback(m_onSearchResultSelectedCallback);
                m_view.RemoveSearchClearedCallback(m_onSearchResultsClearedCallback);
            }

            void SearchWidgetController::OnSearchResultsCleared()
            {
                m_messageBus.Publish(SearchResultSection::SearchResultViewClearedMessage());
            }

            void SearchWidgetController::OnSearchResultSelected(int& index)
            {
                const SearchServicesResult::TSdkSearchResult& sdkSearchResult = m_searchServices.GetSdkSearchResultByIndex(index);

                m_messageBus.Publish(SearchResultSection::SearchResultSectionItemSelectedMessage(
                    sdkSearchResult.GetIdentifier(),
                    sdkSearchResult.GetLocation().ToECEF(),
                    sdkSearchResult.IsInterior(),
                    sdkSearchResult.GetBuildingId(),
                    sdkSearchResult.GetFloor(),
                    m_searchServices.GetResultOriginalIndexFromCurrentIndex(index),
                    sdkSearchResult.GetIdentifier()));
            }

            void SearchWidgetController::OnSearchQueryRefreshedMessage(const Search::SearchQueryRefreshedMessage& message)
            {
                const Search::SdkModel::SearchQuery& query = message.Query();

                m_view.RefreshSearch(query.Query(), QueryContext(query.IsTag(),
                                                                 query.ShouldTryInteriorSearch(),
                                                                 message.Location(),
                                                                 message.Radius()));
            }
        }
    }
}