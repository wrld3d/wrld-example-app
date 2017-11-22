// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "InteriorsPositionConnectionMessage.h"

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        InteriorsPositionConnectionMessage::InteriorsPositionConnectionMessage(bool isConnected)
        : m_isConnected(isConnected)
        {
        }
        
        const bool InteriorsPositionConnectionMessage::IsConnected() const
        {
            return m_isConnected;
        }
    }
}