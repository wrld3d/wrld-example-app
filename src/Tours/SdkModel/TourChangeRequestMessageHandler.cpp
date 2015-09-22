// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourChangeRequestMessageHandler.h"
#include "ITourRepository.h"
#include "ITourService.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            TourChangeRequestMessageHandler::TourChangeRequestMessageHandler(ITourRepository& tourRepository,
                                                                                       ITourService& tourService,
                                                                                       ExampleAppMessaging::TMessageBus& messageBus)
            : m_tourRepository(tourRepository)
            , m_tourService(tourService)
            , m_messageBus(messageBus)
            , m_binding(this, &TourChangeRequestMessageHandler::HandleTourChangeRequest)
            {
                m_messageBus.SubscribeNative(m_binding);
            }
            
            TourChangeRequestMessageHandler::~TourChangeRequestMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_binding);
            }
            
            void TourChangeRequestMessageHandler::HandleTourChangeRequest(const TourChangeRequestMessage& message)
            {
                if(m_tourRepository.ContainsTourModelWithName(message.GetTourName()))
                {
                    TourModel tourModel = m_tourRepository.GetTourModelWithName(message.GetTourName());
                    
                    m_tourService.EnqueueNextTour(tourModel);
                }
            }
        }
    }
}
