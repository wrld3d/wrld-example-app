// Copyright eeGeo Ltd (2012-2018), All Rights Reserved

#include "NavRoutingWorldPinsVisibilityHandler.h"
#include "INavTurnByTurnModel.h"
#include "IWorldPinsVisibilityController.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            NavRoutingWorldPinsVisibilityHandler::NavRoutingWorldPinsVisibilityHandler(ExampleAppMessaging::TMessageBus& messageBus,
                                                                                       WorldPins::SdkModel::IWorldPinsVisibilityController& worldPinsVisibilityController)
            : m_messageBus(messageBus)
            , m_worldPinsVisibilityController(worldPinsVisibilityController)
            , m_viewOpenedMessageHandler(this, &NavRoutingWorldPinsVisibilityHandler::OnNavWidgetViewOpened)
            , m_viewClosedMessageHandler(this, &NavRoutingWorldPinsVisibilityHandler::OnNavWidgetViewClosed)
            {
                m_messageBus.SubscribeNative(m_viewOpenedMessageHandler);
                m_messageBus.SubscribeNative(m_viewClosedMessageHandler);
            }
            
            NavRoutingWorldPinsVisibilityHandler::~NavRoutingWorldPinsVisibilityHandler()
            {
                m_messageBus.UnsubscribeNative(m_viewClosedMessageHandler);
                m_messageBus.UnsubscribeNative(m_viewOpenedMessageHandler);
            }
            
            void NavRoutingWorldPinsVisibilityHandler::OnNavWidgetViewOpened(const NavRoutingViewOpenedMessage& message)
            {
                m_worldPinsVisibilityController.Hide();
            }
            
            void NavRoutingWorldPinsVisibilityHandler::OnNavWidgetViewClosed(const NavRoutingViewClosedMessage& message)
            {
                m_worldPinsVisibilityController.Show();
            }
        }
    }
}
