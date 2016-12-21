// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace SenionLab
    {
        class SenionLabLocationChangedMessage
        {
        public:
        	SenionLabLocationChangedMessage(Eegeo::Space::LatLong& latLong, int floorIndex)
			: m_latLong(latLong)
			, m_floorIndex(floorIndex)
			{
			}

			Eegeo::Space::LatLong& GetLocation() const { return m_latLong; }
			int GetFloorIndex() const { return m_floorIndex; }

		private:
			Eegeo::Space::LatLong& m_latLong;
			int m_floorIndex;
		};
    }
}
