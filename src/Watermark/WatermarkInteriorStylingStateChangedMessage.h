// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Watermark
    {
        class WatermarkInteriorStylingStateChangedMessage
        {
        public:
            WatermarkInteriorStylingStateChangedMessage(bool useInteriorStyling)
            : m_shouldUseInteriorStyling(useInteriorStyling)
            {
            }
            
            bool ShouldUseInteriorStyling() const { return m_shouldUseInteriorStyling; }
            
        private:
            const bool m_shouldUseInteriorStyling;
        };
    }
}
