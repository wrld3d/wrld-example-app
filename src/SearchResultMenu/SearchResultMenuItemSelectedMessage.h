// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "VectorMath.h"
#include "Interiors.h"
#include "InteriorId.h"

namespace ExampleApp
{
    namespace SearchResultMenu
    {
        class SearchResultMenuItemSelectedMessage
        {
            Eegeo::dv3 m_searchResultModelLocationEcef;
            bool m_isInterior;
            Eegeo::Resources::Interiors::InteriorId m_interiorId;
            int m_floorIndex;

        public:
            SearchResultMenuItemSelectedMessage(const Eegeo::dv3& searchResultModelLocationEcef,
                                                const bool isInterior,
                                                const Eegeo::Resources::Interiors::InteriorId& interiorId,
                                                const int floorIndex
            );

            const Eegeo::dv3& SearchResultLocationEcef() const;
            const bool InInterior() const;
            const Eegeo::Resources::Interiors::InteriorId& InteriorBuildingId() const;
            const int FloorIndex() const;
        };
    }
}
