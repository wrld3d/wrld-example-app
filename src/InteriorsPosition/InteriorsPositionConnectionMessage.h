// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        class InteriorsPositionConnectionMessage
        {
        public:
            InteriorsPositionConnectionMessage(bool isConnected);
            
            const bool IsConnected() const;
            
        private:
            bool m_isConnected;
        };
    }
}
