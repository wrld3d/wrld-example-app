// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "Menu.h"
#include "BidirectionalBus.h"
#include "MyPinAddedToMenuMessage.h"
#include "IMenuReactionModel.h"
#include "IMenuIgnoredReactionModel.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace View
        {
            class MyPinAddedToMenuObserver
            {
            public:
                MyPinAddedToMenuObserver(Menu::View::IMenuViewModel& menuViewModel,
                                         Menu::View::IMenuOptionsModel& menuOptionsModel,
                                         ExampleAppMessaging::TMessageBus& messageBus,
                                         const Menu::View::IMenuReactionModel& menuReaction,
                                         Menu::View::IMenuIgnoredReactionModel& ignoredMenuReaction);

                ~MyPinAddedToMenuObserver();

            private:
                Menu::View::IMenuViewModel& m_menuViewModel;
                Menu::View::IMenuOptionsModel& m_menuOptionsModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                const Menu::View::IMenuReactionModel& m_menuReaction;
                Menu::View::IMenuIgnoredReactionModel& m_ignoredMenuReaction;
                Eegeo::Helpers::TCallback1<MyPinAddedToMenuObserver, const MyPinAddedToMenuMessage&> m_handlerBinding;

                void OnMyPinAddedToMenuMessage(const MyPinAddedToMenuMessage& message);
            };
        }
    }
}
