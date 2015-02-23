// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Options
    {
        class CacheEnabledChangedMessage
        {
            bool m_cacheEnabled;
            
        public:
            CacheEnabledChangedMessage(bool cacheEnabled);
            
            bool CacheEnabled() const;
        };
    }
}
