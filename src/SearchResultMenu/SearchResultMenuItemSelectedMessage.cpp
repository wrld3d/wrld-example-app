// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultMenuItemSelectedMessage.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        SearchResultMenuItemSelectedMessage::SearchResultMenuItemSelectedMessage(const Eegeo::dv3& searchResultModelLocationEcef,
                                                                                 const bool isInterior,
                                                                                 const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                                                 const int floorIndex
        )
        : m_searchResultModelLocationEcef(searchResultModelLocationEcef)
        , m_isInterior(isInterior)
        , m_interiorId(interiorId)
        , m_floorIndex(floorIndex)
        {
        }

        const Eegeo::dv3& SearchResultMenuItemSelectedMessage::SearchResultLocationEcef() const
        {
            return m_searchResultModelLocationEcef;
        }
        
        const bool SearchResultMenuItemSelectedMessage::InInterior() const
        {
            return m_isInterior;
        }
        
        const Eegeo::Resources::Interiors::InteriorId& SearchResultMenuItemSelectedMessage::InteriorBuildingId() const
        {
            return m_interiorId;
        }
        
        const int SearchResultMenuItemSelectedMessage::FloorIndex() const
        {
            return m_floorIndex;
        }
    }
}
