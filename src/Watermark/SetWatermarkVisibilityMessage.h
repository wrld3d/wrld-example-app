// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace Watermark
    {
        class SetWatermarkVisibilityMessage
        {
        public:
            
            SetWatermarkVisibilityMessage(bool setVisible)
            : m_setVisible(setVisible)
            {
            }
            
            bool GetShouldSetVisible() const { return m_setVisible; }
            
        private:
            bool m_setVisible;
        };
    }
}
