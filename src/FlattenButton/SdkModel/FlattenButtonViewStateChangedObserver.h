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
                const std::shared_ptr<IFlattenButtonModel> m_flattenButtonModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback1<FlattenButtonViewStateChangedObserver, const FlattenButtonViewStateChangedMessage&> m_handlerBinding;

                void OnFlattenButtonStateChangedMessage(const FlattenButtonViewStateChangedMessage& message);

            public:
                FlattenButtonViewStateChangedObserver(const std::shared_ptr<IFlattenButtonModel>& flattenButtonModel,
                                                      const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);

                ~FlattenButtonViewStateChangedObserver();
            };
        }
    }
}
