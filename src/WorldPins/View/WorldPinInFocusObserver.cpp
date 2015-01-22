// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinInFocusObserver.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        WorldPinInFocusObserver::WorldPinInFocusObserver(IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                                                         ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
        : m_worldPinInFocusViewModel(worldPinInFocusViewModel)
        , m_nativeToUiMessageBus(nativeToUiMessageBus)
        , m_gainedFocusHandler(this, &WorldPinInFocusObserver::HandleReceivedWorldPinGainedFocusMessage)
        , m_lostFocusHandler(this, &WorldPinInFocusObserver::HandleReceivedWorldPinLostFocusMessage)
        , m_focusScreenLocationUpdatedHandler(this, &WorldPinInFocusObserver::HandleReceivedWorldPinInFocusChangedLocationMessage)
        {
            m_nativeToUiMessageBus.Subscribe(m_gainedFocusHandler);
            m_nativeToUiMessageBus.Subscribe(m_lostFocusHandler);
            m_nativeToUiMessageBus.Subscribe(m_focusScreenLocationUpdatedHandler);
        }
        
        WorldPinInFocusObserver::~WorldPinInFocusObserver()
        {
            m_nativeToUiMessageBus.Unsubscribe(m_gainedFocusHandler);
            m_nativeToUiMessageBus.Unsubscribe(m_lostFocusHandler);
            m_nativeToUiMessageBus.Unsubscribe(m_focusScreenLocationUpdatedHandler);
        }
        
        void WorldPinInFocusObserver::HandleReceivedWorldPinGainedFocusMessage(const WorldPinGainedFocusMessage& message)
        {
            m_worldPinInFocusViewModel.Open(message.FocussedModel(), message.ScreenLocation());
            
        }
        
        void WorldPinInFocusObserver::HandleReceivedWorldPinLostFocusMessage(const WorldPinLostFocusMessage& message)
        {
            m_worldPinInFocusViewModel.Close();
        }
        
        void WorldPinInFocusObserver::HandleReceivedWorldPinInFocusChangedLocationMessage(const WorldPinInFocusChangedLocationMessage& message)
        {
            m_worldPinInFocusViewModel.UpdateScreenLocation(message.ScreenLocation());
        }
    }
}
