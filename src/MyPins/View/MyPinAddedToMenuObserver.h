// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "Menu.h"
#include "BidirectionalBus.h"
#include "MyPinAddedToMenuMessage.h"
#include "IMenuReactionModel.h"
#include "IMenuIgnoredReactionModel.h"
#include "MyPinMenuOption.h"
#include "SettingsMenu.h"
#include <memory>

namespace ExampleApp
{
    namespace MyPins
    {
        namespace View
        {
            class MyPinAddedToMenuObserver : private Eegeo::NonCopyable
            {
            public:
                MyPinAddedToMenuObserver(const std::shared_ptr<SettingsMenu::View::SettingsMenuViewModel>& menuViewModel,
                                         const std::shared_ptr<View::MyPinsMenuOptionsModel>& menuOptionsModel,
                                         const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                         const std::shared_ptr<Menu::View::IMenuReactionModel>& menuReaction,
                                         const std::shared_ptr<Menu::View::IModalityIgnoredReactionModel>& ignoredMenuReaction);

                ~MyPinAddedToMenuObserver();

            private:
                const std::shared_ptr<Menu::View::IMenuViewModel> m_menuViewModel;
                const std::shared_ptr<Menu::View::IMenuOptionsModel> m_menuOptionsModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<const Menu::View::IMenuReactionModel> m_menuReaction;
                const std::shared_ptr<Menu::View::IModalityIgnoredReactionModel> m_ignoredMenuReaction;
                Eegeo::Helpers::TCallback1<MyPinAddedToMenuObserver, const MyPinAddedToMenuMessage&> m_handlerBinding;

                void OnMyPinAddedToMenuMessage(const MyPinAddedToMenuMessage& message);
            };
        }
    }
}
