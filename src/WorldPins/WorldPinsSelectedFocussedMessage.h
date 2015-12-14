// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace WorldPins
    {
        class WorldPinsSelectedFocussedMessage
        {
        public:
            WorldPinsSelectedFocussedMessage(int pinId);
            
            int PinId() const;
            
        private:
            int m_pinId;
        };
    }
}
