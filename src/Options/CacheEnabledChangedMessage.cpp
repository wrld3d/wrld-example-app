// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CacheEnabledChangedMessage.h"

namespace ExampleApp
{
    namespace Options
    {
        CacheEnabledChangedMessage::CacheEnabledChangedMessage(bool cacheEnabled)
        : m_cacheEnabled(cacheEnabled)
        {
            
        }
        
        bool CacheEnabledChangedMessage::CacheEnabled() const
        {
            return m_cacheEnabled;
        }
    }
}
