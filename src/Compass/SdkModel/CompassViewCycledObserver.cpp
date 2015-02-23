// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompassViewCycledObserver.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            CompassViewCycledObserver::CompassViewCycledObserver(ICompassModel& model,
                    ExampleAppMessaging::TMessageBus& messageBus
                                                                )
                : m_model(model)
                , m_messageBus(messageBus)
                , m_handler(this, &CompassViewCycledObserver::OnCompassViewCycledMessage)
            {
                m_messageBus.SubscribeNative(m_handler);
            }

            CompassViewCycledObserver::~CompassViewCycledObserver()
            {
                m_messageBus.UnsubscribeNative(m_handler);
            }

            void CompassViewCycledObserver::OnCompassViewCycledMessage(const CompassViewCycledMessage& message)
            {
                m_model.CycleToNextGpsMode();
            }
        }
    }
}
