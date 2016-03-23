// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IModalityModel.h"
#include "ICallback.h"
#include "BidirectionalBus.h"
#include "ModalityChangedMessage.h"

namespace ExampleApp
{
    namespace Modality
    {
        namespace View
        {
            class ModalityObserver : private Eegeo::NonCopyable
            {
                IModalityModel& m_modalityModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback0<ModalityObserver> m_modalityChangedCallback;

                void HandleModalityChanged();

            public:
                ModalityObserver(IModalityModel& modalityModel,
                                 ExampleAppMessaging::TMessageBus& messageBus);

                ~ModalityObserver();
            };
        }
    }
}
