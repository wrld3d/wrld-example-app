//
// Created by david.crooks on 01/03/2018.
//

#pragma once

#include "BidirectionalBus.h"
#include "CallbackCollection.h"
#include "ISearchWidgetView.h"

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

                Eegeo::Helpers::TCallback0<SearchWidgetController> m_onSearchClearedCallback;

            public:
                SearchWidgetController(ISearchWidgetView& view,
                                       ExampleAppMessaging::TMessageBus& messageBus);
                ~SearchWidgetController();

                void OnSearchCleared();
            };
        }
    }
}
