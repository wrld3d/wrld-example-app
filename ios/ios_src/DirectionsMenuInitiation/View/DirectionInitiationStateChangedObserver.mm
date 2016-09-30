// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionInitiationStateChangedObserver.h"
#include "DirectionsMenuInitiationView.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        namespace View
        {
            DirectionInitiationStateChangedObserver::DirectionInitiationStateChangedObserver(                                                                                     DirectionsMenuInitiationView* m_directionMenuView, ExampleAppMessaging::TMessageBus& messageBus)
            : m_messageBus(messageBus)
            , m_directionsMenuStateChangedCallback(this, &DirectionInitiationStateChangedObserver::OnDirectionsMenuStateChanged)
            , m_directionMenuView(m_directionMenuView)
            {
                m_messageBus.SubscribeUi(m_directionsMenuStateChangedCallback);
            }
                
            DirectionInitiationStateChangedObserver::~DirectionInitiationStateChangedObserver()
            {
                m_messageBus.UnsubscribeUi(m_directionsMenuStateChangedCallback);
            }
            
            void DirectionInitiationStateChangedObserver::OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message){
                
                if(message.GetDirectionsMenuStage() == DirectionsMenuInitiation::Inactive)
                {
                    // Inactive
                    [m_directionMenuView SetBtnStateInActive];
                }
                if(message.GetDirectionsMenuStage() == DirectionsMenuInitiation::Active)
                {
                    // Active
                    [m_directionMenuView SetBtnStateActive];
                }
            }
        }
    }
}
