// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "Menu.h"
#include "UiToNativeMessageBus.h"
#include "NativeToUiMessageBus.h"
#include "MyPinRemovedFromMenuMessage.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinRemovedFromMenuObserver
        {
        public:
            MyPinRemovedFromMenuObserver(Menu::IMenuOptionsModel& menuOptionsModel,
                                         ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);
            
            ~MyPinRemovedFromMenuObserver();
            
        private:
            Menu::IMenuOptionsModel& m_menuOptionsModel;
            ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
            
            Eegeo::Helpers::TCallback1<MyPinRemovedFromMenuObserver, const MyPinRemovedFromMenuMessage&> m_handlerBinding;
            
            void HandleReceivedMyRemovedFromMenuMessage(const MyPinRemovedFromMenuMessage& message);
        };
    }
}
