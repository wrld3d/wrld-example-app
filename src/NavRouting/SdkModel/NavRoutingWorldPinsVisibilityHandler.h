// Copyright eeGeo Ltd (2012-2018), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "WorldPins.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingWorldPinsVisibilityHandler : private Eegeo::NonCopyable
            {
            public:
                NavRoutingWorldPinsVisibilityHandler(ExampleAppMessaging::TMessageBus& messageBus,
                                                     WorldPins::SdkModel::IWorldPinsVisibilityController& worldPinsVisibilityController);
                ~NavRoutingWorldPinsVisibilityHandler();
                
            private:
                ExampleAppMessaging::TMessageBus& m_messageBus;
                WorldPins::SdkModel::IWorldPinsVisibilityController& m_worldPinsVisibilityController;
                
                Eegeo::Helpers::TCallback1<NavRoutingWorldPinsVisibilityHandler, const NavRoutingViewOpenedMessage&> m_viewOpenedMessageHandler;
                Eegeo::Helpers::TCallback1<NavRoutingWorldPinsVisibilityHandler, const NavRoutingViewClosedMessage&> m_viewClosedMessageHandler;
                
                void OnNavWidgetViewOpened(const NavRoutingViewOpenedMessage& message);
                void OnNavWidgetViewClosed(const NavRoutingViewClosedMessage& message);

            };
        }
    }
}
