// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

#include "Types.h"
#include "space.h"


namespace ExampleApp
{
    namespace DirectionsMenu
    {
        class DirectionMenuFindDirectionMessage
        {
//          std::string m_searchQuery;
            
            bool m_isInterior;
            const Eegeo::Space::LatLongAltitude &m_startLoc;
            const Eegeo::Space::LatLongAltitude &m_endLoc;
            
        public:
            
            DirectionMenuFindDirectionMessage(const Eegeo::Space::LatLongAltitude &startLocation, const Eegeo::Space::LatLongAltitude &endLocation, bool isInterior);
            const std::string& SearchQuery() const;
            const Eegeo::Space::LatLongAltitude& StartLocation() const;
            const Eegeo::Space::LatLongAltitude& EndLocation() const;
            bool IsInterior() const;
        };
    }
}