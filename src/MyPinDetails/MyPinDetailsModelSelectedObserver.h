// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "NativeToUiMessageBus.h"
#include "ICallback.h"
#include "MyPinDetailsModelSelectedMessage.h"
#include "IMyPinDetailsViewModel.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        class MyPinDetailsModelSelectedObserver : private Eegeo::NonCopyable
        {
            MyPinDetails::IMyPinDetailsViewModel& m_myPinDetailsViewModel;
            ExampleAppMessaging::NativeToUiMessageBus& m_nativeToUiMessageBus;
            Eegeo::Helpers::TCallback1<MyPinDetailsModelSelectedObserver, const MyPinDetailsModelSelectedMessage&> m_handlerBinding;
            
            void HandleReceivedMyPinDetailsModelSelectedMessage(const MyPinDetailsModelSelectedMessage& message);
            
        public:
            MyPinDetailsModelSelectedObserver(MyPinDetails::IMyPinDetailsViewModel& myPinDetailsViewModel,
                                                       ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus);
            
            ~MyPinDetailsModelSelectedObserver();
        };
    }
}
