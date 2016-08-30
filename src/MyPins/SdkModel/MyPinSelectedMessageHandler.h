// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "MyPins.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "IPlaceJumpController.h"
#include "ICallback.h"
#include "MyPinSelectedMessage.h"
#include "CameraTransitions.h"
#include <memory>

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinSelectedMessageHandler : private Eegeo::NonCopyable
            {
                const std::shared_ptr<CameraTransitions::SdkModel::ICameraTransitionController> m_cameraTransitionController;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback1<MyPinSelectedMessageHandler, const MyPinSelectedMessage&> m_handlerBinding;

                void OnMyPinSelectedMessage(const MyPinSelectedMessage& message);

            public:
                MyPinSelectedMessageHandler(const std::shared_ptr<CameraTransitions::SdkModel::ICameraTransitionController>& cameraTransitionController,
                                            const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~MyPinSelectedMessageHandler();

            };
        }
    }
}
