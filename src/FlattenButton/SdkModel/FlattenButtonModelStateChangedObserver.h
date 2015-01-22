// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "IFlattenButtonModel.h"
#include "FlattenButtonViewStateChangedObserver.h"
#include "FlattenButtonModelStateChangedMessage.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace SdkModel
        {
            class FlattenButtonModelStateChangedObserver
            {
                IFlattenButtonModel& m_flattenButtonModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback0<FlattenButtonModelStateChangedObserver> m_flattenStateChangedCallback;

                void HandleFlattenStateChanged();

            public:
                FlattenButtonModelStateChangedObserver(IFlattenButtonModel& flattenButtonModel,
                                                       ExampleAppMessaging::TMessageBus& messageBus);

                ~FlattenButtonModelStateChangedObserver();
            };
        }
    }
}
