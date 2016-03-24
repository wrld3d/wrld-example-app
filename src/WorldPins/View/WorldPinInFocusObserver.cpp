// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinInFocusObserver.h"

#include "WorldPinsSelectedFocussedMessage.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            WorldPinInFocusObserver::WorldPinInFocusObserver(IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    const Menu::View::IMenuReactionModel& menuReaction)
                : m_worldPinInFocusViewModel(worldPinInFocusViewModel)
                , m_messageBus(messageBus)
                , m_gainedFocusHandler(this, &WorldPinInFocusObserver::OnWorldPinGainedFocusMessage)
                , m_lostFocusHandler(this, &WorldPinInFocusObserver::OnWorldPinLostFocusMessage)
                , m_focusScreenLocationUpdatedHandler(this, &WorldPinInFocusObserver::OnWorldPinInFocusChangedLocationMessage)
                , m_selectedFocussedResultHandler(this, &WorldPinInFocusObserver::OnSelectedFocussedResultEvent)
                , m_menuReaction(menuReaction)
            {
                m_messageBus.SubscribeUi(m_gainedFocusHandler);
                m_messageBus.SubscribeUi(m_lostFocusHandler);
                m_messageBus.SubscribeUi(m_focusScreenLocationUpdatedHandler);
                m_worldPinInFocusViewModel.InsertSelectedFocussedResultCallback(m_selectedFocussedResultHandler);
            }

            WorldPinInFocusObserver::~WorldPinInFocusObserver()
            {
                m_messageBus.UnsubscribeUi(m_gainedFocusHandler);
                m_messageBus.UnsubscribeUi(m_lostFocusHandler);
                m_messageBus.UnsubscribeUi(m_focusScreenLocationUpdatedHandler);
                m_worldPinInFocusViewModel.RemoveSelectedFocussedResultCallback(m_selectedFocussedResultHandler);
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
            
            void WorldPinInFocusObserver::OnSelectedFocussedResultEvent()
            {
                if (m_menuReaction.GetShouldOpenMenu())
                {
                    if (m_worldPinInFocusViewModel.IsOpen())
                    {
                        int pinId = m_worldPinInFocusViewModel.GetWorldPinsInFocusModel().GetPinId();
                        m_messageBus.Publish(WorldPinsSelectedFocussedMessage(pinId));
                    }
                }
                else
                {
                    int pinId = m_worldPinInFocusViewModel.GetWorldPinsInFocusModel().GetPinId();
                    m_messageBus.Publish(WorldPinsSelectedFocussedMessage(pinId));
                }
            }
        }
    }
}
