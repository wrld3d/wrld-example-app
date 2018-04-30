// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace WorldPins
    {
        class WorldPinsVisibilityMessage
        {
        public:
            WorldPinsVisibilityMessage(bool pinsVisible);

            const bool ShouldSetVisible() const
            {
                return m_pinsVisible;
            }
  
        private:
            bool m_pinsVisible;
            
        };
    }
}
