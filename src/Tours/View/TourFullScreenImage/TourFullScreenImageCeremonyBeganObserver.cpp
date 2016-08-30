// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourFullScreenImageCeremonyBeganObserver.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourFullScreenImage
            {
                TourFullScreenImageCeremonyBeganObserver::TourFullScreenImageCeremonyBeganObserver(const std::shared_ptr<ITourFullScreenImageViewModel>& tourFullScreenImageViewModel,
                                                                                                   const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus)
                : m_tourFullScreenImageViewModel(tourFullScreenImageViewModel)
                , m_messageBus(messageBus)
                , m_binding(this, &TourFullScreenImageCeremonyBeganObserver::HandleTourFullScreenImageCeremonyBegan)
                {
                    
                    m_messageBus->SubscribeUi(m_binding);
                }
                
                TourFullScreenImageCeremonyBeganObserver::~TourFullScreenImageCeremonyBeganObserver()
                {
                    m_messageBus->UnsubscribeUi(m_binding);
                }
                
                void TourFullScreenImageCeremonyBeganObserver::HandleTourFullScreenImageCeremonyBegan(const TourFullScreenImageCeremonyBeganMessage& message)
                {
                    m_tourFullScreenImageViewModel->BeginFullScreenImageCeremony(message.GetImage(),
                                                                                message.GetMessage());
                }
            }
        }
    }
}
