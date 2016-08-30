// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "Options.h"
#include "CompletedCacheClearMessage.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            class CompletedCacheClearMessageHandler : private Eegeo::NonCopyable
            {
                const std::shared_ptr<IOptionsViewModel> m_optionsViewModel;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback1<CompletedCacheClearMessageHandler, const CompletedCacheClearMessage&> m_messageHandlerBinding;
                
                void OnCompletedCacheClear(const CompletedCacheClearMessage& message);
                
            public:
                CompletedCacheClearMessageHandler(const std::shared_ptr<IOptionsViewModel>& optionsViewModel,
                                                  const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);
                
                ~CompletedCacheClearMessageHandler();
            };
        }
    }
}
