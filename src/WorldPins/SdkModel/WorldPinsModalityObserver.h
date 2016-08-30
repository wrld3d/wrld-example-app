// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ModalityChangedMessage.h"
#include "IWorldPinsScaleController.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinsModalityObserver : private Eegeo::NonCopyable
            {
                const std::shared_ptr<IWorldPinsScaleController>& m_worldPinsScaleController;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus>& m_messageBus;
                Eegeo::Helpers::TCallback1<WorldPinsModalityObserver, const Modality::ModalityChangedMessage&> m_handlerBinding;

                void OnModalityChangedMessage(const Modality::ModalityChangedMessage& message);

            public:
                WorldPinsModalityObserver(const std::shared_ptr<IWorldPinsScaleController>& worldPinsScaleController,
                                          const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~WorldPinsModalityObserver();
            };
        }
    }
}
