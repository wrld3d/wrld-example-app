// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "TourFullScreenImageCeremonyBeganMessage.h"
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
                class TourFullScreenImageCeremonyBeganObserver : private Eegeo::NonCopyable
                {
                    const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                    const std::shared_ptr<ITourFullScreenImageViewModel> m_tourFullScreenImageViewModel;
                    Eegeo::Helpers::TCallback1<TourFullScreenImageCeremonyBeganObserver, const TourFullScreenImageCeremonyBeganMessage&> m_binding;
                    
                    void HandleTourFullScreenImageCeremonyBegan(const TourFullScreenImageCeremonyBeganMessage& message);
                    
                public:
                    TourFullScreenImageCeremonyBeganObserver(const std::shared_ptr<ITourFullScreenImageViewModel>& tourFullScreenImageViewModel,
                                                             const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);
                    
                    ~TourFullScreenImageCeremonyBeganObserver();
                };
            }
        }
    }
}
