// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace SdkModel
        {
            struct NavRouteDrawingVertexData
            {
                NavRouteDrawingVertexData(double latitudeDegrees, double longitudeDegrees, const std::string& indoorMapId, int indoorMapFloorId, bool multiFloor);
                
                bool operator != (const NavRouteDrawingVertexData& rhs) const;
                
                bool operator == (const NavRouteDrawingVertexData& rhs) const;
                
                double GetLatitudeDegrees() const;
                double GetLongitudeDegrees() const;
                const std::string& GetIndoorMapId() const;
                int GetIndoorMapFloorId() const;
                bool IsMultiFloor() const;
            private:
                double m_latitudeDegrees;
                double m_longitudeDegrees;
                std::string m_indoorMapId;
                int m_indoorMapFloorId;
                bool m_multiFloor;
            };
        }
    }
}
