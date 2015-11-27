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
            WatermarkAlignmentStateChangedMessage(bool shouldAlignBottom)
            : m_shouldAlignBottom(shouldAlignBottom)
            {
            }
            
            bool ShouldAlignBottom() const {return m_shouldAlignBottom;}
            
        private:
            const bool m_shouldAlignBottom;
            
        };
    }
}