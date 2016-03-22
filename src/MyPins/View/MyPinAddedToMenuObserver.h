// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "Menu.h"
#include "BidirectionalBus.h"
#include "MyPinAddedToMenuMessage.h"
#include "IMenuReactionModel.h"

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
                                         const Menu::View::IMenuReactionModel& menuReaction);

                ~MyPinAddedToMenuObserver();

            private:
                Menu::View::IMenuViewModel& m_menuViewModel;
                Menu::View::IMenuOptionsModel& m_menuOptionsModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                const Menu::View::IMenuReactionModel& m_menuReaction;
                Eegeo::Helpers::TCallback1<MyPinAddedToMenuObserver, const MyPinAddedToMenuMessage&> m_handlerBinding;

                void OnMyPinAddedToMenuMessage(const MyPinAddedToMenuMessage& message);
            };
        }
    }
}
