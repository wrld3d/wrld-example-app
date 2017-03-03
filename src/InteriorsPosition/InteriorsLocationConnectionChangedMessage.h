// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        class InteriorsLocationConnectionChangedMessage
        {
        public:
            InteriorsLocationConnectionChangedMessage(const bool isConnected)
                : m_isConnected(isConnected)
            {}

            const bool IsConnected() const
            {
                return m_isConnected;
            }

        private:
            bool m_isConnected;
        };
    }
}
