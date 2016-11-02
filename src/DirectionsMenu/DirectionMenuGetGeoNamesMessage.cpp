// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "DirectionMenuGetGeoNamesMessage.h"

namespace ExampleApp
{
    namespace DirectionsMenu
    {
        DirectionMenuGetGeoNamesMessage::DirectionMenuGetGeoNamesMessage(const std::string &startLocationQuery, bool isInterior, bool isStartLocation):
        m_searchQuery(startLocationQuery)
        , m_isInterior(isInterior)
        , m_isStartLocation(isStartLocation)
        {
        }
        
        bool DirectionMenuGetGeoNamesMessage::IsInterior() const
        {
            return m_isInterior;
        }
        
        bool DirectionMenuGetGeoNamesMessage::IsStartLocation() const
        {
            return m_isStartLocation;
        }
                
        const std::string& DirectionMenuGetGeoNamesMessage::SearchQuery() const
        {
            return m_searchQuery;
        }
    }
}
