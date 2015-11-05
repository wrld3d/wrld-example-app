// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "URLRequestedMessage.h"

namespace ExampleApp
{
    namespace URLRequest
    {
        URLRequestedMessage::URLRequestedMessage(const std::string& url)
        : m_url(url)
        {
            
        }
        
        std::string URLRequestedMessage::URL() const
        {
            return m_url;
        }
    }
}