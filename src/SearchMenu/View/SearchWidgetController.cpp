//
// Created by david.crooks on 01/03/2018.
//

#include "SearchWidgetController.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            SearchWidgetController::SearchWidgetController(ISearchWidgetView& view,
                                                           ExampleAppMessaging::TMessageBus& messageBus)
            : m_view(view)
            , m_messageBus(messageBus)
            , m_onSearchResultsClearedCallback(this, &SearchWidgetController::OnSearchResultsCleared)
            {
                m_view.InsertSearchClearedCallback(m_onSearchResultsClearedCallback);
            }

            SearchWidgetController::~SearchWidgetController()
            {
                m_view.RemoveSearchClearedCallback(m_onSearchResultsClearedCallback);
            }

            void SearchWidgetController::OnSearchResultsCleared()
            {
                m_messageBus.Publish(SearchResultSection::SearchResultViewClearedMessage());
            }
        }
    }
}