// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace Direction
    {
        namespace SdkModel
        {
            class DirectionRouteGeometryModel
            {
            public:
                
                DirectionRouteGeometryModel(std::string type, const  std::vector<Eegeo::Space::LatLong>& coordinates);
                ~DirectionRouteGeometryModel();
                const std::string& GetType() const;
                const std::vector<Eegeo::Space::LatLong>& GetCoordinates();
                
            private:
                
                std::vector<Eegeo::Space::LatLong> m_coordinates;
                std::string m_type;

                

                
            };
        }
    }
}
