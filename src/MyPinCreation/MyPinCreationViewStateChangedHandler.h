// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IMyPinCreationModel.h"
#include "UiToNativeMessageBus.h"
#include "ICallback.h"
#include "MyPinCreationViewStateChangedMessage.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        class MyPinCreationViewStateChangedHandler
        {
        public:
            
            MyPinCreationViewStateChangedHandler(IMyPinCreationModel& myPinCreationModel,
                                                 ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
            : m_myPinCreationModel(myPinCreationModel)
            , m_uiToNativeMessageBus(uiToNativeMessageBus)
            , m_handler(this, &MyPinCreationViewStateChangedHandler::OnMyPinCreationViewStateChangedMessageReceived)
            {
                m_uiToNativeMessageBus.Subscribe(m_handler);
            }
            
            ~MyPinCreationViewStateChangedHandler()
            {
                m_uiToNativeMessageBus.Unsubscribe(m_handler);
            }

        private:
            IMyPinCreationModel& m_myPinCreationModel;
            ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
            
            Eegeo::Helpers::TCallback1<MyPinCreationViewStateChangedHandler, const MyPinCreationViewStateChangedMessage&> m_handler;
            
            void OnMyPinCreationViewStateChangedMessageReceived(const MyPinCreationViewStateChangedMessage& message)
            {
                m_myPinCreationModel.SetCreationStage(message.GetMyPinCreationStage());
            }
        };
    }
}
