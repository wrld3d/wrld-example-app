// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "AppModes.h"
#include "ISearchResultMenuViewModel.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        namespace View
        {
            class SearchResultMenuAppModeMessageHandler : private Eegeo::NonCopyable
            {
                ISearchResultMenuViewModel& m_searchResultMenuViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<SearchResultMenuAppModeMessageHandler, const AppModes::AppModeChangedMessage&> m_handlerBinding;
                
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
                
            public:
                SearchResultMenuAppModeMessageHandler(ISearchResultMenuViewModel& searchResultMenuViewModel,
                                                      ExampleAppMessaging::TMessageBus& messageBus);
                
                ~SearchResultMenuAppModeMessageHandler();
            };
        }
    }
}
