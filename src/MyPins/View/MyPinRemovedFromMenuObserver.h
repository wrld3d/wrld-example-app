// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "Menu.h"
#include "BidirectionalBus.h"
#include "MyPinMenuOption.h"
#include "MyPinRemovedFromMenuMessage.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace View
        {
            class MyPinRemovedFromMenuObserver : private Eegeo::NonCopyable
            {
            public:
                MyPinRemovedFromMenuObserver(const std::shared_ptr<MyPinsMenuOptionsModel>& menuOptionsModel,
                                             const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~MyPinRemovedFromMenuObserver();

            private:
                const std::shared_ptr<Menu::View::IMenuOptionsModel> m_menuOptionsModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;

                Eegeo::Helpers::TCallback1<MyPinRemovedFromMenuObserver, const MyPinRemovedFromMenuMessage&> m_handlerBinding;

                void OnMyRemovedFromMenuMessage(const MyPinRemovedFromMenuMessage& message);
            };
        }
    }
}
