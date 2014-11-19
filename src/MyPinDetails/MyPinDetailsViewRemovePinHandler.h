// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMyPinCreationModel.h"
#include "UiToNativeMessageBus.h"
#include "ICallback.h"
#include "MyPinDetailsViewRemovePinMessage.h"
#include "MyPins.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        class MyPinDetailsViewRemovePinHandler
        {
        public:
            
            MyPinDetailsViewRemovePinHandler(MyPins::IMyPinsService& myPinsService,
                                             ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);
            
            ~MyPinDetailsViewRemovePinHandler();
            
        private:;
            MyPins::IMyPinsService& m_myPinsService;
            ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
            
            Eegeo::Helpers::TCallback1<MyPinDetailsViewRemovePinHandler, const MyPinDetailsViewRemovePinMessage&> m_handler;
            
            void OnMyPinCreationViewSavePinMessageReceived(const MyPinDetailsViewRemovePinMessage& message);
        };
    }
}
