// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once
#include "MyPins.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "IPlaceJumpController.h"
#include "ICallback.h"
#include "MyPinSelectedMessage.h"
#include "CameraTransitions.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinSelectedMessageHandler
            {
                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<MyPinSelectedMessageHandler, const MyPinSelectedMessage&> m_handlerBinding;

                void OnMyPinSelectedMessage(const MyPinSelectedMessage& message);

            public:
                MyPinSelectedMessageHandler(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                                            ExampleAppMessaging::TMessageBus& messageBus);

                ~MyPinSelectedMessageHandler();

            };
        }
    }
}
