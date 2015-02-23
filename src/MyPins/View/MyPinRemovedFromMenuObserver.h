// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "Menu.h"
#include "BidirectionalBus.h"
#include "MyPinRemovedFromMenuMessage.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace View
        {
            class MyPinRemovedFromMenuObserver
            {
            public:
                MyPinRemovedFromMenuObserver(Menu::View::IMenuOptionsModel& menuOptionsModel,
                                             ExampleAppMessaging::TMessageBus& messageBus);

                ~MyPinRemovedFromMenuObserver();

            private:
                Menu::View::IMenuOptionsModel& m_menuOptionsModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Helpers::TCallback1<MyPinRemovedFromMenuObserver, const MyPinRemovedFromMenuMessage&> m_handlerBinding;

                void OnMyRemovedFromMenuMessage(const MyPinRemovedFromMenuMessage& message);
            };
        }
    }
}
