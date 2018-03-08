// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include "BidirectionalBus.h"
#include "CallbackCollection.h"
#include "ISearchWidgetView.h"
#include "SearchServices.h"
#include "SearchQueryRefreshedMessage.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchWidgetController {
            private:
                ISearchWidgetView& m_view;
                ExampleAppMessaging::TMessageBus& m_messageBus;
				SearchServices& m_searchServices;

                Eegeo::Helpers::TCallback0<SearchWidgetController> m_onSearchResultsClearedCallback;
                Eegeo::Helpers::TCallback1<SearchWidgetController, int> m_onSearchResultSelectedCallback;
				Eegeo::Helpers::TCallback1<SearchWidgetController, const Search::SearchQueryRefreshedMessage&>
																		m_onSearchQueryRefreshedHandler;

            public:
                SearchWidgetController(ISearchWidgetView& view,
                                       ExampleAppMessaging::TMessageBus& messageBus,
									   SearchServices& searchServices);
                ~SearchWidgetController();

                void OnSearchResultsCleared();
                void OnSearchResultSelected(int& index);

				void OnSearchQueryRefreshedMessage(const Search::SearchQueryRefreshedMessage& message);
            };
        }
    }
}
