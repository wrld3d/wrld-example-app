// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavigateToMessage.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        NavigateToMessage::NavigateToMessage(
                const std::string& title,
                const Eegeo::Space::LatLong& location,
                const bool isInterior,
                const Eegeo::Resources::Interiors::InteriorId& buildingId,
                const int floor)
        : m_name(title)
        , m_latLon(location)
        , m_isIndoors(isInterior)
        , m_indoorMapId(buildingId)
        , m_indoorMapFloorId(floor)
        {

        }
        const std::string& NavigateToMessage::GetTitle() const
        {
            return m_name;
        }

        const Eegeo::Space::LatLong& NavigateToMessage::GetLocation() const
        {
            return m_latLon;
        }

        const bool NavigateToMessage::IsInterior() const
        {
            return m_isIndoors;
        }

        const Eegeo::Resources::Interiors::InteriorId& NavigateToMessage::GetBuildingId() const
        {
            return m_indoorMapId;
        }

        const int NavigateToMessage::GetFloor() const
        {
            return m_indoorMapFloorId;
        }
    }
}
