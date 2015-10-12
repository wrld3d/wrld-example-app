// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace WorldPins
    {
        class WorldPinsVisibilityMessage
        {
        public:
            WorldPinsVisibilityMessage(int visibilityMask);

            const bool ShouldSetVisible() const
            {
                return m_setVisible;
            }
            
            const int VisibilityMask() const
            {
                return m_visibilityMask;
            }

        private:
            bool m_setVisible;
            
            int m_visibilityMask;
        };
    }
}