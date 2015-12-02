// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace URLRequest
    {
        class URLRequestedMessage
        {
        private:
            
            const std::string m_url;
            
        public:
            
            URLRequestedMessage(const std::string& url);
            
            std::string URL() const;
        };
    }
}
