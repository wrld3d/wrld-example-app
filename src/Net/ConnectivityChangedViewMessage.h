// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Net
    {
        class ConnectivityChangedViewMessage
        {
        public:
            ConnectivityChangedViewMessage(const bool isConnected)
            : m_isConnected(isConnected)
            {
            }
            
            bool IsConnected() const { return m_isConnected; }
            
        private:
            bool m_isConnected;
        };
    }
}