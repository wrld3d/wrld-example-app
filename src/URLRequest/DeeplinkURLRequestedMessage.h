// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace URLRequest
    {
        class DeeplinkURLRequestedMessage
        {
        private:
            
            const std::string m_deeplinkUrl;
            const std::string m_httpFallbackUrl;
            
        public:
            
            DeeplinkURLRequestedMessage(const std::string& deeplinkUrl, const std::string& httpFallbackUrl);
            
            const std::string& DeeplinkURL() const;
            const std::string& HttpFallbackURL() const;
        };
    }
}
