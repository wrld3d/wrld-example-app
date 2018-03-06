//
// Created by david.crooks on 01/03/2018.
//

#pragma once

#include "BidirectionalBus.h"
#include "CallbackCollection.h"
#include "ISearchWidgetView.h"
#include "SearchServices.h"

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

            public:
                SearchWidgetController(ISearchWidgetView& view,
                                       ExampleAppMessaging::TMessageBus& messageBus,
									   SearchServices& searchServices);
                ~SearchWidgetController();

                void OnSearchResultsCleared();
                void OnSearchResultSelected(int& index);
            };
        }
    }
}
