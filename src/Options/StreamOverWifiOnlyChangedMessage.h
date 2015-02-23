// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Options
    {
        class StreamOverWifiOnlyChangedMessage
        {
            bool m_streamOverWifiOnly;
            
        public:
            StreamOverWifiOnlyChangedMessage(bool streamOverWifiOnly);
            
            bool StreamOverWifiOnly() const;
        };
    }
}
