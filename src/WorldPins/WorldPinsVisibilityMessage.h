// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace WorldPins
    {
        class WorldPinsVisibilityMessage
        {
        public:
            WorldPinsVisibilityMessage(bool setVisible);
            
            const bool ShouldSetVisible() const { return m_setVisible; }
            
        private:
            bool m_setVisible;
        };
    }
}