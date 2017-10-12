// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InteriorsPosition
    {
        class InteriorsLocationChangedMessage
        {
        public:
            InteriorsLocationChangedMessage(const double latitude, const double longitude, const std::string& floorId)
            : m_latitude(latitude)
            , m_longitude(longitude)
            , m_floorId(floorId)
            {}

            const double Latitude() const
            {
                return m_latitude;
            }

            const double Longitude() const
            {
                return m_longitude;
            }

            const std::string& FloorId() const
            {
                return m_floorId;
            }

        private:
            double m_latitude;
            double m_longitude;
            std::string m_floorId;
        };
    }
}
