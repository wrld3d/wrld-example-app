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
                const std::shared_ptr<ICompassModel> m_model;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback0<CompassModeObserver> m_callback;
                Eegeo::Helpers::TCallback0<CompassModeObserver> m_unauthorizedCallback;

                void OnGpsModeChanged();
                void OnGpsModeDeniedBecauseUnauthorized();

            public:
                CompassModeObserver(const std::shared_ptr<ICompassModel>& model,
                                    const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~CompassModeObserver();
            };
        }
    }
}
