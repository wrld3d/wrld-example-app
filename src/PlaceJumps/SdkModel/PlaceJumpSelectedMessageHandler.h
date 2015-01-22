// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "IPlaceJumpController.h"
#include "ICallback.h"
#include "PlaceJumpSelectedMessage.h"

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace SdkModel
        {
            class PlaceJumpSelectedMessageHandler : private Eegeo::NonCopyable
            {
                IPlaceJumpController& m_placeJumpController;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<PlaceJumpSelectedMessageHandler, const PlaceJumpSelectedMessage&> m_handlerBinding;

                void OnPlaceJumpSelectedMessage(const PlaceJumpSelectedMessage& message);

            public:
                PlaceJumpSelectedMessageHandler(
                    IPlaceJumpController& placeJumpController,
                    ExampleAppMessaging::TMessageBus& messageBus);

                ~PlaceJumpSelectedMessageHandler();
            };
        }
    }
}
