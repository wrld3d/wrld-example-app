#pragma once

#include "NavRouting.h"
#include "VectorMath.h"

#include <string>

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            class NavRoutingPolylineCreateParams
            {
            public:
                NavRoutingPolylineCreateParams(
                    const std::vector<Eegeo::Space::LatLong>& coordinates,
                    const Eegeo::v4& color,
                    const std::string &indoorMapId,
                    int indoorMapFloorId,
                    const std::vector<double>& perPointElevations
                )
                : m_coordinates(coordinates)
                , m_color(color)
                , m_indoorMapId(indoorMapId)
                , m_indoorMapFloorId(indoorMapFloorId)
                , m_perPointElevations(perPointElevations)
                {}

                const std::vector<Eegeo::Space::LatLong>& GetCoordinates() const { return m_coordinates; }
                const Eegeo::v4& GetColor() const { return m_color; }
                const std::string& GetIndoorMapId() const { return m_indoorMapId; }
                int GetIndoorMapFloorId() const { return m_indoorMapFloorId; }
                const std::vector<double>& GetPerPointElevations() const { return m_perPointElevations; }
                bool IsIndoor() const { return !m_indoorMapId.empty(); }

            private:
                std::vector<Eegeo::Space::LatLong> m_coordinates;
                Eegeo::v4 m_color;
                std::string m_indoorMapId;
                int m_indoorMapFloorId;
                std::vector<double> m_perPointElevations;
            };

        }
    }
}
