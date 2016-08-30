// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourActiveStateChangedMessageHandler.h"
#include "ITourService.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            TourActiveStateChangedMessageHandler::TourActiveStateChangedMessageHandler(const std::shared_ptr<ITourService>& tourService,
                                                                                       const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus)
            : m_tourService(tourService)
            , m_messageBus(messageBus)
            , m_binding(this, &TourActiveStateChangedMessageHandler::HandleTourActiveStateChanged)
            {
                m_messageBus->SubscribeNative(m_binding);
            }
            
            TourActiveStateChangedMessageHandler::~TourActiveStateChangedMessageHandler()
            {
                m_messageBus->UnsubscribeNative(m_binding);
            }
            
            void TourActiveStateChangedMessageHandler::HandleTourActiveStateChanged(const TourActiveStateChangedMessage& message)
            {
                m_tourService->SetActiveTourState(message.GetActiveStateIndex());
            }
        }
    }
}
