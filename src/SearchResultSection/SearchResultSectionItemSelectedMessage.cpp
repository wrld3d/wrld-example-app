// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultSectionItemSelectedMessage.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        SearchResultSectionItemSelectedMessage::SearchResultSectionItemSelectedMessage(const Eegeo::dv3& searchResultModelLocationEcef,
                                                                                       const bool isInterior,
                                                                                       const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                                                       const int floorIndex,
                                                                                       int itemIndex,
                                                                                       const std::string modelIdentifier)
        : m_searchResultModelLocationEcef(searchResultModelLocationEcef)
        , m_isInterior(isInterior)
        , m_interiorId(interiorId)
        , m_floorIndex(floorIndex)
        , m_itemIndex(itemIndex)
        , m_modelIdentifier(modelIdentifier)
        {
            
        }

        const Eegeo::dv3& SearchResultSectionItemSelectedMessage::SearchResultLocationEcef() const
        {
            return m_searchResultModelLocationEcef;
        }
        
        const bool SearchResultSectionItemSelectedMessage::InInterior() const
        {
            return m_isInterior;
        }
        
        const Eegeo::Resources::Interiors::InteriorId& SearchResultSectionItemSelectedMessage::InteriorBuildingId() const
        {
            return m_interiorId;
        }
        
        const int SearchResultSectionItemSelectedMessage::FloorIndex() const
        {
            return m_floorIndex;
        }

        int SearchResultSectionItemSelectedMessage::ItemIndex() const
        {
            return m_itemIndex;
        }
        
        const std::string& SearchResultSectionItemSelectedMessage::ModelIdentifier() const
        {
            return m_modelIdentifier;
        }
    }
}
