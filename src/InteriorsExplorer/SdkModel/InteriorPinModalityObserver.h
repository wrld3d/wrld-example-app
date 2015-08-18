// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "ModalityChangedMessage.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorPinModalityObserver : private Eegeo::NonCopyable
            {
            public:
                InteriorPinModalityObserver(ExampleAppMessaging::TMessageBus& messageBus);
                ~InteriorPinModalityObserver();
                
            private:
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                Eegeo::Helpers::TCallback1<InteriorPinModalityObserver, const Modality::ModalityChangedMessage&> m_handlerBinding;
                void OnModalityChangedMessage(const Modality::ModalityChangedMessage& message);
            };
        }
    }
}