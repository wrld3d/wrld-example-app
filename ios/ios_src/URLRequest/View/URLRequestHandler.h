// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "URLRequestedMessage.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include <string>

namespace ExampleApp
{
    namespace URLRequest
    {
        namespace View
        {
            class URLRequestHandler : private Eegeo::NonCopyable
            {
            private:
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                Eegeo::Helpers::TCallback1<URLRequestHandler, const URLRequestedMessage&> m_urlRequestedCallback;
                void OnURLRequested(const URLRequestedMessage& message);
                
            public:
                
                URLRequestHandler(ExampleAppMessaging::TMessageBus& messageBus);
                
                ~URLRequestHandler();
                
            };
        }
    }
}