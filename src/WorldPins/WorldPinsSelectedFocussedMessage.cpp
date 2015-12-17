// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldPinsSelectedFocussedMessage.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        WorldPinsSelectedFocussedMessage::WorldPinsSelectedFocussedMessage(int pinId)
        : m_pinId(pinId)
        {
        }
        
        int WorldPinsSelectedFocussedMessage::PinId() const
        {
            return m_pinId;
        }

    }
}