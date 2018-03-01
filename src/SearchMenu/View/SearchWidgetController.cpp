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
            , m_onSearchClearedCallback(this, &SearchWidgetController::OnSearchCleared)
            {
                m_view.InsertSearchClearedCallback(m_onSearchClearedCallback);
            }

            SearchWidgetController::~SearchWidgetController()
            {
                m_view.RemoveSearchClearedCallback(m_onSearchClearedCallback);
            }

            void SearchWidgetController::OnSearchCleared()
            {

            }
        }
    }
}