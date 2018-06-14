// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        class NavigateToMessage
        {
        private:
            const std::string& m_name;
            const Eegeo::Space::LatLong& m_latLon;
            const bool m_isIndoors;
            const Eegeo::Resources::Interiors::InteriorId& m_indoorMapId;
            const int m_indoorMapFloorId;

        public:
            NavigateToMessage(
                    const std::string& title,
                    const Eegeo::Space::LatLong& location,
                    const bool isInterior,
                    const Eegeo::Resources::Interiors::InteriorId& buildingId,
                    const int floor);

            const std::string& GetTitle() const;
            const Eegeo::Space::LatLong& GetLocation() const;
            const bool IsInterior() const;
            const Eegeo::Resources::Interiors::InteriorId& GetBuildingId() const;
            const int GetFloor() const;

        };
    }
}
