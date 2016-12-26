// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICompassModel.h"
#include "ICallback.h"
#include "CompassModeChangedMessage.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace SdkModel
        {
            class CompassModeObserver : private Eegeo::NonCopyable
            {
            private:
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback0<CompassModeObserver> m_callback;
                Eegeo::Helpers::TCallback0<CompassModeObserver> m_unauthorizedCallback;

            protected:
                ICompassModel& m_model;
                virtual void OnGpsModeChanged();
                virtual void OnGpsModeDeniedBecauseUnauthorized();

            public:
                CompassModeObserver(ICompassModel& model,
                                    ExampleAppMessaging::TMessageBus& messageBus);

                virtual ~CompassModeObserver();
            };
        }
    }
}
