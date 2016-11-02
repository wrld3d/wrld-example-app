// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

#include "Types.h"
#include "space.h"


namespace ExampleApp
{
    namespace DirectionsMenu
    {
        class DirectionMenuGetGeoNamesMessage
        {
            std::string m_searchQuery;
            
            bool m_isInterior;
            
            bool m_isStartLocation;
            
        public:
            
            DirectionMenuGetGeoNamesMessage(const std::string &startLocationQuery, bool isInterior, bool isStartLocation);
            const std::string& SearchQuery() const;
            const Eegeo::Space::LatLongAltitude& StartLocation() const;
            const Eegeo::Space::LatLongAltitude& EndLocation() const;
            bool IsInterior() const;
            bool IsStartLocation() const;
        };
    }
}