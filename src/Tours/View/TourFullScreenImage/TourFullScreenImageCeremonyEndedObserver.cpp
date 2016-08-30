// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourFullScreenImageCeremonyEndedObserver.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace View
        {
            namespace TourFullScreenImage
            {
                TourFullScreenImageCeremonyEndedObserver::TourFullScreenImageCeremonyEndedObserver(const std::shared_ptr<ITourFullScreenImageViewModel>& tourFullScreenImageViewModel,
                                                                                                   const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus)
                : m_tourFullScreenImageViewModel(tourFullScreenImageViewModel)
                , m_messageBus(messageBus)
                , m_binding(this, &TourFullScreenImageCeremonyEndedObserver::HandleTourFullScreenImageCeremonyEnded)
                {
                    
                    m_messageBus->SubscribeUi(m_binding);
                }
                
                TourFullScreenImageCeremonyEndedObserver::~TourFullScreenImageCeremonyEndedObserver()
                {
                    m_messageBus->UnsubscribeUi(m_binding);
                }
                
                void TourFullScreenImageCeremonyEndedObserver::HandleTourFullScreenImageCeremonyEnded(const TourFullScreenImageCeremonyEndedMessage& message)
                {
                    m_tourFullScreenImageViewModel->EndFullScreenImageCeremony();
                }
            }
        }
    }
}
