// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

// eeGeo SDK includes
#include "ICallback.h"
#include "Types.h"
// App includes
#include "BidirectionalBus.h"
#include "UserInteraction.h"

namespace ExampleApp
{
    namespace UserInteraction
    {
        namespace SdkModel
        {
            class UserInteractionEnabledObserver : Eegeo::NonCopyable
            {
            private:
                UserInteractionModel& m_userInteractionModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback0<UserInteractionEnabledObserver> m_userInteractionEnabledChangedHandler;
                
            public:
                UserInteractionEnabledObserver(UserInteractionModel& userInteractionModel, ExampleAppMessaging::TMessageBus& messageBus);
                
                ~UserInteractionEnabledObserver();
                
            private:
                void OnUserInteractionEnabledChanged();
            };
        }
    }
}
