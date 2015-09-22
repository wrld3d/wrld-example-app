// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "ICallback.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "TourChangeRequestMessage.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            class TourChangeRequestMessageHandler : private Eegeo::NonCopyable
            {
                ITourRepository& m_tourRepository;
                ITourService& m_tourService;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                
                Eegeo::Helpers::TCallback1<TourChangeRequestMessageHandler, const TourChangeRequestMessage&> m_binding;
                
                void HandleTourChangeRequest(const TourChangeRequestMessage& message);
                
            public:
                TourChangeRequestMessageHandler(ITourRepository& tourRepository,
                                                ITourService& tourService,
                                                ExampleAppMessaging::TMessageBus& messageBus);
                
                ~TourChangeRequestMessageHandler();
            };
        }
    }
}
