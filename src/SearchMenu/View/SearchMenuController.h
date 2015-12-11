// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuController.h"

#include "SearchMenu.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
        namespace View
        {
            class SearchMenuController : public Menu::View::MenuController
            {
            private:
                ISearchMenuView& m_searchMenuView;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                bool m_appModeAllowsOpen;
                
                Eegeo::Helpers::TCallback2<SearchMenuController, OpenableControl::View::IOpenableControlViewModel&, float> m_onOpenStateChangedCallback;
                Eegeo::Helpers::TCallback1<SearchMenuController, const Search::SearchQueryPerformedMessage&> m_performedQueryHandler;
                Eegeo::Helpers::TCallback1<SearchMenuController, const Search::SearchQueryResponseReceivedMessage&> m_receivedQueryResponseHandler;
                Eegeo::Helpers::TCallback1<SearchMenuController, const std::string&> m_onSearchCallback;
                Eegeo::Helpers::TCallback1<SearchMenuController, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
                
                void OnOpenStateChanged(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState);
                
                void OnSearchQueryPerformedMessage(const Search::SearchQueryPerformedMessage& message);
                
                void OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message);
                
                void OnSearch(const std::string& searchQuery);
                
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
                
                bool TryDrag();
                
                void OnViewClicked();
                
            public:
                SearchMenuController(Menu::View::IMenuModel& model,
                                     Menu::View::IMenuViewModel& viewModel,
                                     Menu::View::IMenuView& view,
                                     ISearchMenuView& searchMenuView,
                                     ExampleAppMessaging::TMessageBus& messageBus);
                
                ~SearchMenuController();
            };
        }
    }
}