// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Interiors.h"
#include "InteriorId.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace SearchResultSection
    {
        class SearchResultSectionItemSelectedMessage
        {
            Eegeo::dv3 m_searchResultModelLocationEcef;
            
            bool m_isInterior;
            Eegeo::Resources::Interiors::InteriorId m_interiorId;
            int m_floorIndex;

            int m_itemIndex;
            
            std::string m_modelIdentifier;

        public:
            SearchResultSectionItemSelectedMessage(const Eegeo::dv3& searchResultModelLocationEcef,
                                                   const bool isInterior,
                                                   const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                   const int floorIndex,
                                                   int itemIndex,
                                                   const std::string modelIdentifier);

            const Eegeo::dv3& SearchResultLocationEcef() const;
            
            const bool InInterior() const;
            
            const Eegeo::Resources::Interiors::InteriorId& InteriorBuildingId() const;
            
            const int FloorIndex() const;

            int ItemIndex() const;
            
            const std::string& ModelIdentifier() const;
        };
    }
}
