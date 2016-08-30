// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "WorldPins.h"
#include "ICallback.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "TourActiveStateChangedMessage.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            class TourActiveStateChangedMessageHandler : private Eegeo::NonCopyable
            {
                const std::shared_ptr<ITourService> m_tourService;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                
                Eegeo::Helpers::TCallback1<TourActiveStateChangedMessageHandler, const TourActiveStateChangedMessage&> m_binding;
                
                void HandleTourActiveStateChanged(const TourActiveStateChangedMessage& message);
                
            public:
                TourActiveStateChangedMessageHandler(const std::shared_ptr<ITourService>& tourService,
                                                     const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);
                
                ~TourActiveStateChangedMessageHandler();
            };
        }
    }
}
