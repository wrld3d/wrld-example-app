// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once
#include "MyPins.h"
#include "Types.h"
#include "UiToNativeMessageBus.h"
#include "IPlaceJumpController.h"
#include "ICallback.h"
#include "MyPinSelectedMessage.h"
#include "CameraTransitions.h"

namespace ExampleApp
{
    namespace MyPins
    {
        class MyPinSelectedMessageHandler
        {
            CameraTransitions::ICameraTransitionController& m_cameraTransitionController;
            ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
            Eegeo::Helpers::TCallback1<MyPinSelectedMessageHandler, const MyPinSelectedMessage&> m_handlerBinding;
            
            void HandleReceivedMyPinSelectedMessage(const MyPinSelectedMessage& message);
            
        public:
            MyPinSelectedMessageHandler(CameraTransitions::ICameraTransitionController& cameraTransitionController,
                                            ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus);
            
            ~MyPinSelectedMessageHandler();

        };
    }
}