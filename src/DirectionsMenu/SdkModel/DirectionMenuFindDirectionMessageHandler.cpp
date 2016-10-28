// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionMenuFindDirectionMessageHandler.h"


namespace ExampleApp
{
    namespace DirectionsMenu
    {
        namespace SdkModel
        {
            DirectionMenuFindDirectionMessageHandler::DirectionMenuFindDirectionMessageHandler(ExampleAppMessaging::TMessageBus& messageBus
                                                                                               ,Direction::SdkModel::FindDirectionQueryPerformer& findDirectionQueryPerformer)
            : m_messageBus(messageBus)
            , m_findDirectionQueryPerformer(findDirectionQueryPerformer)
            , m_handleFindDirectionMessageBinding(this, &DirectionMenuFindDirectionMessageHandler::OnFindDirectionMessage)
            {
                m_messageBus.SubscribeNative(m_handleFindDirectionMessageBinding);
            }
            DirectionMenuFindDirectionMessageHandler::~DirectionMenuFindDirectionMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handleFindDirectionMessageBinding);
            }
            void DirectionMenuFindDirectionMessageHandler::OnFindDirectionMessage(const DirectionsMenu::DirectionMenuFindDirectionMessage& message)
            {
                const Eegeo::Space::LatLongAltitude startLoc = Eegeo::Space::LatLongAltitude::FromDegrees(-2.984219, 56.459917,0.0);
                const Eegeo::Space::LatLongAltitude endLoc = Eegeo::Space::LatLongAltitude::FromDegrees(-2.977156, 56.459778,0.0);
                m_findDirectionQueryPerformer.PerformFindDirectionQuery(startLoc,endLoc, message.IsInterior());
            }

        }
    }
}