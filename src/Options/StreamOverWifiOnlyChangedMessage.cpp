// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "StreamOverWifiOnlyChangedMessage.h"

namespace ExampleApp
{
    namespace Options
    {
        StreamOverWifiOnlyChangedMessage::StreamOverWifiOnlyChangedMessage(bool streamOverWifiOnly)
        : m_streamOverWifiOnly(streamOverWifiOnly)
        {
            
        }
        
        bool StreamOverWifiOnlyChangedMessage::StreamOverWifiOnly() const
        {
            return m_streamOverWifiOnly;
        }
    }
}
