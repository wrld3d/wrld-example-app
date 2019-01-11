// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchServicesResult.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        struct SearchNavigationData
        {
        private:
            const std::string& m_name;
            const Eegeo::Space::LatLong& m_latLon;
            const bool m_isIndoors;
            const Eegeo::Resources::Interiors::InteriorId& m_indoorMapId;
            const int m_indoorMapFloorIndex;
            const std::string& m_jsonData;

        public:
            SearchNavigationData(const Search::SdkModel::SearchResultModel& searchResult);

            const std::string& GetTitle() const;
            const Eegeo::Space::LatLong& GetLocation() const;
            const bool IsInterior() const;
            const Eegeo::Resources::Interiors::InteriorId& GetBuildingId() const;
            const int GetFloorIndex() const;
            const std::string& GetJsonData() const;
        };
    }
}
