// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMyPinCreationModel.h"
#include "UiToNativeMessageBus.h"
#include "ICallback.h"
#include "MyPinCreationViewSavePinMessage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationViewSavePinHandler
        {
        public:
            
            MyPinCreationViewSavePinHandler(IMyPinCreationModel& myPinCreationModel,
                                            ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);
            
            ~MyPinCreationViewSavePinHandler();
            
        private:
            IMyPinCreationModel& m_myPinCreationModel;
            ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
            
            Eegeo::Helpers::TCallback1<MyPinCreationViewSavePinHandler, const MyPinCreationViewSavePinMessage&> m_handler;
            
            void OnMyPinCreationViewSavePinMessageReceived(const MyPinCreationViewSavePinMessage& message);
        };
    }
}
