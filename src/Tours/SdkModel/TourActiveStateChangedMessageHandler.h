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
                ITourService& m_tourService;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                Eegeo::Helpers::TCallback1<TourActiveStateChangedMessageHandler, const TourActiveStateChangedMessage&> m_binding;
                
                void HandleTourActiveStateChanged(const TourActiveStateChangedMessage& message);
                
            public:
                TourActiveStateChangedMessageHandler(ITourService& tourService,
                                                     ExampleAppMessaging::TMessageBus& messageBus);
                
                ~TourActiveStateChangedMessageHandler();
            };
        }
    }
}
