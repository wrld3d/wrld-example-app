// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldPinInFocusViewModel.h"
#include "ICallback.h"
#include "BidirectionalBus.h"
#include "WorldPinGainedFocusMessage.h"
#include "WorldPinLostFocusMessage.h"
#include "WorldPinInFocusChangedLocationMessage.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace View
        {
            class WorldPinInFocusObserver : private Eegeo::NonCopyable
            {
                IWorldPinInFocusViewModel& m_worldPinInFocusViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<WorldPinInFocusObserver, const WorldPinGainedFocusMessage&> m_gainedFocusHandler;
                Eegeo::Helpers::TCallback1<WorldPinInFocusObserver, const WorldPinLostFocusMessage&> m_lostFocusHandler;
                Eegeo::Helpers::TCallback1<WorldPinInFocusObserver, const WorldPinInFocusChangedLocationMessage&> m_focusScreenLocationUpdatedHandler;

                void OnWorldPinGainedFocusMessage(const WorldPinGainedFocusMessage& message);
                void OnWorldPinLostFocusMessage(const WorldPinLostFocusMessage& message);
                void OnWorldPinInFocusChangedLocationMessage(const WorldPinInFocusChangedLocationMessage& message);

            public:
                WorldPinInFocusObserver(IWorldPinInFocusViewModel& worldPinInFocusViewModel,
                                        ExampleAppMessaging::TMessageBus& messageBus);

                ~WorldPinInFocusObserver();
            };
        }
    }
}
