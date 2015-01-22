// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "Menu.h"
#include "BidirectionalBus.h"
#include "MyPinAddedToMenuMessage.h"

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
                                         ExampleAppMessaging::TMessageBus& messageBus);

                ~MyPinAddedToMenuObserver();

            private:
                Menu::View::IMenuViewModel& m_menuViewModel;
                Menu::View::IMenuOptionsModel& m_menuOptionsModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<MyPinAddedToMenuObserver, const MyPinAddedToMenuMessage&> m_handlerBinding;

                void OnMyPinAddedToMenuMessage(const MyPinAddedToMenuMessage& message);
            };
        }
    }
}
