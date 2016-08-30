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
                const std::shared_ptr<IFlattenButtonModel> m_flattenButtonModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback0<FlattenButtonModelStateChangedObserver> m_flattenStateChangedCallback;

                void HandleFlattenStateChanged();

            public:
                FlattenButtonModelStateChangedObserver(const std::shared_ptr<IFlattenButtonModel>& flattenButtonModel,
                                                       const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~FlattenButtonModelStateChangedObserver();
            };
        }
    }
}
