// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ModalityChangedMessage.h"
#include "WorldPins.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsModalityObserver : private Eegeo::NonCopyable
            {
                IWorldPinsVisibilityController& m_worldPinsVisibilityController;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<WorldPinsModalityObserver, const Modality::ModalityChangedMessage&> m_handlerBinding;

                void OnModalityChangedMessage(const Modality::ModalityChangedMessage& message);

            public:
                WorldPinsModalityObserver(IWorldPinsVisibilityController& worldPinsVisibilityController,
                                          ExampleAppMessaging::TMessageBus& messageBus);

                ~WorldPinsModalityObserver();
            };
        }
    }
}
