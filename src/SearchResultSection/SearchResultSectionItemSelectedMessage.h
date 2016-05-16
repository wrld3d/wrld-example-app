// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Interiors.h"
#include "InteriorId.h"
#include "VectorMath.h"

#include <string>

namespace ExampleApp
{
    namespace SearchResultSection
    {
        class SearchResultSectionItemSelectedMessage
        {
            std::string m_searchResultModelIdentifier;
            Eegeo::dv3 m_searchResultModelLocationEcef;
            
            bool m_isInterior;
            Eegeo::Resources::Interiors::InteriorId m_interiorId;
            int m_floorIndex;

            int m_itemIndex;

        public:
            SearchResultSectionItemSelectedMessage(const std::string& searchResultModelIdentifier,
                                                   const Eegeo::dv3& searchResultModelLocationEcef,
                                                   const bool isInterior,
                                                   const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                   const int floorIndex,
                                                   int itemIndex);

            std::string Identifier() const;

            const Eegeo::dv3& SearchResultLocationEcef() const;
            
            const bool InInterior() const;
            
            const Eegeo::Resources::Interiors::InteriorId& InteriorBuildingId() const;
            
            const int FloorIndex() const;

            int ItemIndex() const;
        };
    }
}
