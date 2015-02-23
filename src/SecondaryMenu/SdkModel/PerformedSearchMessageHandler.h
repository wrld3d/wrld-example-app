// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "PerformedSearchMessage.h"
#include "ISearchQueryPerformer.h"

namespace ExampleApp
{
    namespace SecondaryMenu
    {
        namespace SdkModel
        {
            class PerformedSearchMessageHandler : private Eegeo::NonCopyable
            {
                Search::SdkModel::ISearchQueryPerformer& m_searchQueryPerformer;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<PerformedSearchMessageHandler, const PerformedSearchMessage&> m_handlePerformedSearchMessageBinding;

                void OnPerformedSearchMessage(const PerformedSearchMessage& message);

            public:
                PerformedSearchMessageHandler(
                    Search::SdkModel::ISearchQueryPerformer& searchQueryPerformer,
                    ExampleAppMessaging::TMessageBus& messageBus);

                ~PerformedSearchMessageHandler();
            };
        }
    }
}
