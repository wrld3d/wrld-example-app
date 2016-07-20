// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Watermark
    {
        class WatermarkAlignmentStateChangedMessage
        {
        public:
            WatermarkAlignmentStateChangedMessage(bool shouldAlignBottom, bool shouldAlignBelowFloorDisplay)
            : m_shouldAlignBottom(shouldAlignBottom), m_shouldAlignBelowFloorDisplay(shouldAlignBelowFloorDisplay)
            {
            }
            
            bool ShouldAlignBottom() const {return m_shouldAlignBottom;}
            bool ShouldAlignBelowFloorDisplay() const {return m_shouldAlignBelowFloorDisplay;}
            
        private:
            const bool m_shouldAlignBottom;
            const bool m_shouldAlignBelowFloorDisplay;
        };
    }
}
