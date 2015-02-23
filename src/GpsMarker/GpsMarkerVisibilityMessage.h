// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace GpsMarker
    {
        class GpsMarkerVisibilityMessage
        {
        public:
            GpsMarkerVisibilityMessage(bool setVisible);
            
            const bool ShouldSetVisible() const
            {
                return m_setVisible;
            }
            
        private:
            bool m_setVisible;
        };
    }
}