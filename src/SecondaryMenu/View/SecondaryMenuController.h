// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MenuController.h"
#include "ISecondaryMenuView.h"
#include "ICallback.h"
#include "Menu.h"
#include "BidirectionalBus.h"
#include "PerformedSearchMessage.h"

#include <string>

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace View
        {
            class SecondaryMenuController : public Menu::View::MenuController
            {
            private:
                ISecondaryMenuView& m_secondaryMenuView;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback2<SecondaryMenuController, OpenableControl::View::IOpenableControlViewModel&, float> m_onOpenStateChangedCallback;
                Eegeo::Helpers::TCallback1<SecondaryMenuController, const Search::SearchQueryPerformedMessage&> m_performedQueryHandler;
                Eegeo::Helpers::TCallback1<SecondaryMenuController, const Search::SearchQueryResponseReceivedMessage&> m_receivedQueryResponseHandler;
                Eegeo::Helpers::TCallback1<SecondaryMenuController, const std::string&> m_onSearchCallback;

                void OnOpenStateChanged(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState);

                void OnSearchQueryPerformedMessage(const Search::SearchQueryPerformedMessage& message);

                void OnSearchQueryResponseReceivedMessage(const Search::SearchQueryResponseReceivedMessage& message);

                void OnSearch(const std::string& searchQuery);
            public:
                SecondaryMenuController(
                    ISecondaryMenuView& secondaryMenuView,
                    Menu::View::IMenuView& menuView,
                    Menu::View::IMenuModel& menuModel,
                    Menu::View::IMenuViewModel& menuViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                ~SecondaryMenuController();
            };
        }
    }
}
