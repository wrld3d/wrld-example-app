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
                    const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                    const std::shared_ptr<ITourFullScreenImageViewModel> m_tourFullScreenImageViewModel;
                    Eegeo::Helpers::TCallback1<TourFullScreenImageCeremonyEndedObserver, const TourFullScreenImageCeremonyEndedMessage&> m_binding;
                    
                    void HandleTourFullScreenImageCeremonyEnded(const TourFullScreenImageCeremonyEndedMessage& message);
                    
                public:
                    TourFullScreenImageCeremonyEndedObserver(const std::shared_ptr<ITourFullScreenImageViewModel>& tourFullScreenImageViewModel,
                                                             const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);
                    
                    ~TourFullScreenImageCeremonyEndedObserver();
                };
            }
        }
    }
}
