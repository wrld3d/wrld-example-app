// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "CompassViewCycledMessage.h"
#include "ICompassModel.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            class CompassViewCycledObserver : private Eegeo::NonCopyable
            {
            private:
                ExampleAppMessaging::TMessageBus& m_messageBus;
                ICompassModel& m_model;
                Eegeo::Helpers::TCallback1<CompassViewCycledObserver, const CompassViewCycledMessage&> m_handler;

                void OnCompassViewCycledMessage(const CompassViewCycledMessage& message);

            public:
                CompassViewCycledObserver(ICompassModel& model,
                                          ExampleAppMessaging::TMessageBus& messageBus
                                         );

                ~CompassViewCycledObserver();
            };
        }
    }
}
