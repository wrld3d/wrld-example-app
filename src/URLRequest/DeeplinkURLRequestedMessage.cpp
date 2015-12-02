// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DeeplinkURLRequestedMessage.h"

namespace ExampleApp
{
    namespace URLRequest
    {
        DeeplinkURLRequestedMessage::DeeplinkURLRequestedMessage(const std::string& deeplinkUrl, const std::string& httpFallbackUrl)
        : m_deeplinkUrl(deeplinkUrl)
        , m_httpFallbackUrl(httpFallbackUrl)
        {
            
        }
        
        const std::string& DeeplinkURLRequestedMessage::DeeplinkURL() const
        {
            return m_deeplinkUrl;
        }
        const std::string& DeeplinkURLRequestedMessage::HttpFallbackURL() const
        {
            return m_httpFallbackUrl;
        }
    }
}