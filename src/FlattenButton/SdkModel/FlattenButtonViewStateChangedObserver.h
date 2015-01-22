// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "IFlattenButtonModel.h"

namespace ExampleApp
{
    namespace FlattenButton
    {
        namespace SdkModel
        {
            class FlattenButtonViewStateChangedObserver
            {
                IFlattenButtonModel& m_flattenButtonModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<FlattenButtonViewStateChangedObserver, const FlattenButtonViewStateChangedMessage&> m_handlerBinding;

                void OnFlattenButtonStateChangedMessage(const FlattenButtonViewStateChangedMessage& message);

            public:
                FlattenButtonViewStateChangedObserver(IFlattenButtonModel& flattenButtonModel,
                                                      ExampleAppMessaging::TMessageBus& messageBus);

                ~FlattenButtonViewStateChangedObserver();
            };
        }
    }
}
