// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuAppModeMessageHandler.h"
#include "AppModeChangedMessage.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            SearchResultMenuAppModeMessageHandler::SearchResultMenuAppModeMessageHandler(ISearchResultMenuViewModel& searchResultMenuViewModel,
                                                                                         ExampleAppMessaging::TMessageBus& messageBus)
            : m_searchResultMenuViewModel(searchResultMenuViewModel)
            , m_messageBus(messageBus)
            , m_handlerBinding(this, &SearchResultMenuAppModeMessageHandler::OnAppModeChanged)
            {
                m_messageBus.SubscribeUi(m_handlerBinding);
            }
            
            SearchResultMenuAppModeMessageHandler::~SearchResultMenuAppModeMessageHandler()
            {
                m_messageBus.UnsubscribeUi(m_handlerBinding);
            }
            
            void SearchResultMenuAppModeMessageHandler::OnAppModeChanged(const AppModes::AppModeChangedMessage& message)
            {
                bool searchMenuEnabled = message.GetAppMode() != AppModes::SdkModel::TourMode;
                m_searchResultMenuViewModel.SetEnabled(searchMenuEnabled);
            }
        }
    }
}
