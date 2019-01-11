#include "SearchNavigationData.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        SearchNavigationData::SearchNavigationData(const SearchMenu::View::SearchServicesResult::TSdkSearchResult& searchResult)
        : m_name(searchResult.GetTitle())
        , m_latLon(searchResult.GetLocation())
        , m_isIndoors(searchResult.IsInterior())
        , m_indoorMapId(searchResult.GetBuildingId())
        , m_indoorMapFloorIndex(searchResult.GetFloor())
        , m_jsonData(searchResult.GetJsonData())
        {

        }
        const std::string& SearchNavigationData::GetTitle() const
        {
            return m_name;
        }

        const Eegeo::Space::LatLong& SearchNavigationData::GetLocation() const
        {
            return m_latLon;
        }

        const bool SearchNavigationData::IsInterior() const
        {
            return m_isIndoors;
        }

        const Eegeo::Resources::Interiors::InteriorId& SearchNavigationData::GetBuildingId() const
        {
            return m_indoorMapId;
        }

        const int SearchNavigationData::GetFloorIndex() const
        {
            return m_indoorMapFloorIndex;
        }

        const std::string& SearchNavigationData::GetJsonData() const
        {
            return m_jsonData;
        }
    }
}
