// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        class InteriorsPositionLocationChangedMessage
        {
        public:
        	InteriorsPositionLocationChangedMessage(Eegeo::Space::LatLong latLong)
            : m_latLong(latLong)
            {
            }
            
        	Eegeo::Space::LatLong GetLocation() const { return m_latLong; }
            
        private:
            Eegeo::Space::LatLong m_latLong;
        };
    }
}
