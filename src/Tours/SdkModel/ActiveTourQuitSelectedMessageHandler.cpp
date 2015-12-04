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
            ActiveTourQuitSelectedMessageHandler::ActiveTourQuitSelectedMessageHandler(ITourService& tourService,
                                                                                       Search::SdkModel::ISearchRefreshService& searchRefreshService,
                                                                                       ExampleAppMessaging::TMessageBus& messageBus)
            : m_tourService(tourService)
            , m_searchRefreshService(searchRefreshService)
            , m_messageBus(messageBus)
            , m_binding(this, &ActiveTourQuitSelectedMessageHandler::HandleActiveTourQuitSelected)
            {
                m_messageBus.SubscribeNative(m_binding);
            }
            
            ActiveTourQuitSelectedMessageHandler::~ActiveTourQuitSelectedMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_binding);
            }
            
            void ActiveTourQuitSelectedMessageHandler::HandleActiveTourQuitSelected(const ActiveTourQuitSelectedMessage& message)
            {
                m_searchRefreshService.SetEnabled(true);
                if(message.ExitTours())
                {
                    m_tourService.EndAllTours();
                }
                else
                {
                    m_tourService.EndCurrentActiveTour();
                }
            }
        }
    }
}
