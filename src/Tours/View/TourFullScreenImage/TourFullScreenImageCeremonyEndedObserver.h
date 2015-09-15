// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "TourFullScreenImageCeremonyEndedMessage.h"
#include "ITourFullScreenImageViewModel.h"
#include "Types.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourFullScreenImage
            {
                class TourFullScreenImageCeremonyEndedObserver : private Eegeo::NonCopyable
                {
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    ITourFullScreenImageViewModel& m_tourFullScreenImageViewModel;
                    Eegeo::Helpers::TCallback1<TourFullScreenImageCeremonyEndedObserver, const TourFullScreenImageCeremonyEndedMessage&> m_binding;
                    
                    void HandleTourFullScreenImageCeremonyEnded(const TourFullScreenImageCeremonyEndedMessage& message);
                    
                public:
                    TourFullScreenImageCeremonyEndedObserver(ITourFullScreenImageViewModel& tourFullScreenImageViewModel,
                                                             ExampleAppMessaging::TMessageBus& messageBus);
                    
                    ~TourFullScreenImageCeremonyEndedObserver();
                };
            }
        }
    }
}
