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
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<ICompassModel> m_model;
                Eegeo::Helpers::TCallback1<CompassViewCycledObserver, const CompassViewCycledMessage&> m_handler;

                void OnCompassViewCycledMessage(const CompassViewCycledMessage& message);

            public:
                CompassViewCycledObserver(const std::shared_ptr<ICompassModel>& model,
                                          const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus
                                         );

                ~CompassViewCycledObserver();
            };
        }
    }
}
