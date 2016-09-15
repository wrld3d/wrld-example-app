// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "MyPins.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "LoadingScreenCompleteMessage.h"
#include <memory>

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            class MyPinsLoadingMessageHandler : private Eegeo::NonCopyable
            {
                const std::shared_ptr<IMyPinsService> m_myPinsService;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                Eegeo::Helpers::TCallback1<MyPinsLoadingMessageHandler, const LoadingScreenCompleteMessage&> m_handlerBinding;
                
                void OnLoadingScreenCompleteMessage(const LoadingScreenCompleteMessage& message);
                
            public:
                MyPinsLoadingMessageHandler(const std::shared_ptr<IMyPinsService>& myPinsService,
                                            const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus);
                
                ~MyPinsLoadingMessageHandler();
            };
        }
    }
}
