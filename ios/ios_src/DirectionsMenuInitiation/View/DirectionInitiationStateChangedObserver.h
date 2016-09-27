// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "BidirectionalBus.h"
#include "DirectionsMenuStateChangedMessage.h"
#include "DirectionsMenuInitiationView.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        namespace View
        {
            class DirectionInitiationStateChangedObserver
            {
            public:
                DirectionInitiationStateChangedObserver(DirectionsMenuInitiationView* m_directionMenuView,ExampleAppMessaging::TMessageBus& messageBus);
                
                ~DirectionInitiationStateChangedObserver();
                
            private:
                ExampleAppMessaging::TMessageBus& m_messageBus;
                DirectionsMenuInitiationView* m_directionMenuView;
                
                Eegeo::Helpers::TCallback1<DirectionInitiationStateChangedObserver, const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage&> m_directionsMenuStateChangedCallback;
                
                void OnDirectionsMenuStateChanged(const DirectionsMenuInitiation::DirectionsMenuStateChangedMessage& message);
                
            };
        }

    }
}