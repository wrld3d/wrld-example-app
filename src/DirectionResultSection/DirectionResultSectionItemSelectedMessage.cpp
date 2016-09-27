// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionResultSectionItemSelectedMessage.h"

namespace ExampleApp
{
    namespace DirectionResultSection
    {
        DirectionResultSectionItemSelectedMessage::DirectionResultSectionItemSelectedMessage(const Eegeo::dv3& searchResultModelLocationEcef
                                                                                             ,const bool isInterior
                                                                                             ,const Eegeo::Resources::Interiors::InteriorId& interiorId
                                                                                             ,const int floorIndex
                                                                                             ,int itemIndex)
        : m_searchResultModelLocationEcef(searchResultModelLocationEcef)
        , m_isInterior(isInterior)
        , m_interiorId(interiorId)
        , m_floorIndex(floorIndex)
        , m_itemIndex(itemIndex)
        {
        
        }
        DirectionResultSectionItemSelectedMessage::~DirectionResultSectionItemSelectedMessage()
        {
        
        }
        
        const Eegeo::dv3& DirectionResultSectionItemSelectedMessage::SearchResultLocationEcef() const
        {
            return m_searchResultModelLocationEcef;
        }
        
        const bool DirectionResultSectionItemSelectedMessage::InInterior() const
        {
            return m_isInterior;
        }
        
        const Eegeo::Resources::Interiors::InteriorId& DirectionResultSectionItemSelectedMessage::InteriorBuildingId() const
        {
            return m_interiorId;
        }
        
        const int DirectionResultSectionItemSelectedMessage::FloorIndex() const
        {
            return m_floorIndex;
        }
        
        int DirectionResultSectionItemSelectedMessage::ItemIndex() const
        {
            return m_itemIndex;
        }
        
    }
}