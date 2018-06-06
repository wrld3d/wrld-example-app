// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        class InteriorsLocationChangedMessage
        {
        public:
            InteriorsLocationChangedMessage(const double latitude,
                                            const double longitude,
                                            const double horizontalAccuracyInMeters,
                                            const int floorNumber)
            : m_latitude(latitude)
            , m_longitude(longitude)
            , m_horizontalAccuracyInMeters(horizontalAccuracyInMeters)
            , m_hasAccuracy(true)
            , m_floorNumber(floorNumber)
            {}

            InteriorsLocationChangedMessage(const double latitude,
                                            const double longitude,
                                            const int floorNumber)
                    : m_latitude(latitude)
                    , m_longitude(longitude)
                    , m_horizontalAccuracyInMeters(0)
                     ,m_hasAccuracy(false)
                    , m_floorNumber(floorNumber)
            {}

            const double Latitude() const
            {
                return m_latitude;
            }

            const double Longitude() const
            {
                return m_longitude;
            }

            const bool HasAccuracy() const
            {
                return m_hasAccuracy;
            }

            const double HorizontalAccuracyInMeters() const
            {
                return m_horizontalAccuracyInMeters;
            }

            const int FloorNumber() const
            {
                return m_floorNumber;
            }

        private:
            double m_latitude;
            double m_longitude;
            double m_horizontalAccuracyInMeters;
            bool m_hasAccuracy;
            int m_floorNumber;
        };
    }
}
