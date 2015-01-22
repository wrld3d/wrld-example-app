// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinInFocusObserver.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            WorldPinInFocusObserver::WorldPinInFocusObserver(IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus)
                : m_worldPinInFocusViewModel(worldPinInFocusViewModel)
                , m_messageBus(messageBus)
                , m_gainedFocusHandler(this, &WorldPinInFocusObserver::OnWorldPinGainedFocusMessage)
                , m_lostFocusHandler(this, &WorldPinInFocusObserver::OnWorldPinLostFocusMessage)
                , m_focusScreenLocationUpdatedHandler(this, &WorldPinInFocusObserver::OnWorldPinInFocusChangedLocationMessage)
            {
                m_messageBus.SubscribeUi(m_gainedFocusHandler);
                m_messageBus.SubscribeUi(m_lostFocusHandler);
                m_messageBus.SubscribeUi(m_focusScreenLocationUpdatedHandler);
            }

            WorldPinInFocusObserver::~WorldPinInFocusObserver()
            {
                m_messageBus.UnsubscribeUi(m_gainedFocusHandler);
                m_messageBus.UnsubscribeUi(m_lostFocusHandler);
                m_messageBus.UnsubscribeUi(m_focusScreenLocationUpdatedHandler);
            }

            void WorldPinInFocusObserver::OnWorldPinGainedFocusMessage(const WorldPinGainedFocusMessage& message)
            {
                m_worldPinInFocusViewModel.Open(message.FocussedModel(), message.ScreenLocation());

            }

            void WorldPinInFocusObserver::OnWorldPinLostFocusMessage(const WorldPinLostFocusMessage& message)
            {
                m_worldPinInFocusViewModel.Close();
            }

            void WorldPinInFocusObserver::OnWorldPinInFocusChangedLocationMessage(const WorldPinInFocusChangedLocationMessage& message)
            {
                m_worldPinInFocusViewModel.UpdateScreenLocation(message.ScreenLocation());
            }
        }
    }
}
