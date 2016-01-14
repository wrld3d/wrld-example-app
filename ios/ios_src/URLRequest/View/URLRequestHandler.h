// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "URLRequestedMessage.h"
#include "DeeplinkURLRequestedMessage.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "LinkOutObserver.h"
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
                LinkOutObserver::LinkOutObserver& m_linkOutObserver;
                Eegeo::Helpers::TCallback1<URLRequestHandler, const URLRequestedMessage&> m_urlRequestedCallback;
                Eegeo::Helpers::TCallback1<URLRequestHandler, const DeeplinkURLRequestedMessage&> m_deeplinkUrlRequestedCallback;
                void OnURLRequested(const URLRequestedMessage& message);
                void OnDeeplinkURLRequested(const DeeplinkURLRequestedMessage& message);
                
            public:
                
                URLRequestHandler(ExampleAppMessaging::TMessageBus& messageBus,
                                  LinkOutObserver::LinkOutObserver& linkOutObserver);
                
                ~URLRequestHandler();
                
                void RequestExternalURL(const std::string& url);
                
                void RequestDeeplinkURL(const std::string& deeplinkUrl, const std::string& httpFallbackUrl);
                
                bool CanHandleDeeplinkURL(const std::string& deeplinkUrl);
            };
        }
    }
}