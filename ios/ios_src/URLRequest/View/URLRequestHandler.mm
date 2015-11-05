// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "URLRequestHandler.h"


namespace ExampleApp
{
    namespace URLRequest
    {
        namespace View
        {
            URLRequestHandler::URLRequestHandler(ExampleAppMessaging::TMessageBus& messageBus)
            : m_messageBus(messageBus)
            , m_urlRequestedCallback(this, &URLRequestHandler::OnURLRequested)
            {
                m_messageBus.SubscribeUi(m_urlRequestedCallback);
            }
            
            URLRequestHandler::~URLRequestHandler()
            {
                m_messageBus.UnsubscribeUi(m_urlRequestedCallback);
            }
            
            void URLRequestHandler::OnURLRequested(const ExampleApp::URLRequest::URLRequestedMessage &message)
            {
                NSString *urlLink = [NSString stringWithUTF8String:message.URL().c_str()];
                [[UIApplication sharedApplication] openURL:[NSURL URLWithString:urlLink]];
            }
        }
    }
}