// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        class InteriorsLocationChangedMessage
        {
        public:
            InteriorsLocationChangedMessage(
                    const double latitude,
                    const double longitude,
                    const double horizontalAccuracyInMeters,
                    const int vendorSpecificFloorNumber)
            : m_latitude(latitude)
            , m_longitude(longitude)
            , m_horizontalAccuracyInMetres(horizontalAccuracyInMeters)
            , m_vendorSpecificFloorNumber(vendorSpecificFloorNumber)
            {

            }

            const double LatitudeDegrees() const
            {
                return m_latitude;
            }

            const double LongitudeDegrees() const
            {
                return m_longitude;
            }

            const double HorizontalAccuracyInMeters() const
            {
                return m_horizontalAccuracyInMetres;
            }

            const int VendorSpecificFloorNumber() const
            {
                return m_vendorSpecificFloorNumber;
            }


        private:
            double m_latitude;
            double m_longitude;
            double m_horizontalAccuracyInMetres;
            int m_vendorSpecificFloorNumber;
        };
    }
}
