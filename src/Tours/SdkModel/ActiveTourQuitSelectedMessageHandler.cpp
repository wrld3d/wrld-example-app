// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ActiveTourQuitSelectedMessageHandler.h"
#include "ITourService.h"
#include "ISearchRefreshService.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            ActiveTourQuitSelectedMessageHandler::ActiveTourQuitSelectedMessageHandler(const std::shared_ptr<ITourService>& tourService,
                                                                                       const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus)
            : m_tourService(tourService)
            , m_messageBus(messageBus)
            , m_binding(this, &ActiveTourQuitSelectedMessageHandler::HandleActiveTourQuitSelected)
            {
                m_messageBus->SubscribeNative(m_binding);
            }
            
            ActiveTourQuitSelectedMessageHandler::~ActiveTourQuitSelectedMessageHandler()
            {
                m_messageBus->UnsubscribeNative(m_binding);
            }
            
            void ActiveTourQuitSelectedMessageHandler::HandleActiveTourQuitSelected(const ActiveTourQuitSelectedMessage& message)
            {
                if(message.ExitTours())
                {
                    m_tourService->EndAllTours();
                }
                else
                {
                    m_tourService->EndCurrentActiveTour();
                }
            }
        }
    }
}
