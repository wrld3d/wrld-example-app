// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            /*
             3: Yelp support (27/2/15)
             4: Added review count (7/7/15)
             5: Refactored search result model footprint (24/9/15)

             6: Changes to format:

                ~ Rename humanReadableCategories (string[]) => humanReadableTags
                - Remove category (string)
                + Add iconKey (string)
                + Add tags (string[])

                Also: Removed support for all prior versions. (XX/09/15)
             */
            const int SearchResultModel::CurrentVersion = 6;
            
            SearchResultModel::SearchResultModel()
            : m_version(-1)
            , m_identifier("")
            , m_title("")
            , m_subtitle("")
            , m_location(Eegeo::Space::LatLong(0.f, 0.f))
            , m_heightAboveTerrainMetres(0.0f)
            , m_interior(false)
            , m_building("")
            , m_floor(0)
            , m_iconKey("")
            , m_humanReadableTags()
            , m_vendor("")
            , m_jsonData("")
            , m_searchResultCreationTimeStamp(-1)
            {
                
            }
            
            SearchResultModel::SearchResultModel(int version,
                                                 const std::string& identifier,
                                                 const std::string& title,
                                                 const std::string& subtitle,
                                                 const Eegeo::Space::LatLong& location,
                                                 float heightAboveTerrainMetres,
                                                 bool interior,
                                                 const Eegeo::Resources::Interiors::InteriorId& building,
                                                 int floor,
                                                 const std::vector<std::string>& tags,
                                                 const std::vector<std::string>& humanReadableTags,
                                                 const TagIconKey& iconKey,
                                                 const std::string& vendor,
                                                 const std::string& jsonData,
                                                 int64_t searchResultCreationTimeStamp)
            : m_version(version)
            , m_identifier(identifier)
            , m_title(title)
            , m_subtitle(subtitle)
            , m_location(location)
            , m_heightAboveTerrainMetres(heightAboveTerrainMetres)
            , m_interior(interior)
            , m_building(building)
            , m_floor(floor)
            , m_tags(tags)
            , m_humanReadableTags(humanReadableTags)
            , m_iconKey(iconKey)
            , m_vendor(vendor)
            , m_jsonData(jsonData)
            , m_searchResultCreationTimeStamp(searchResultCreationTimeStamp)
            {                
                Eegeo_ASSERT(!identifier.empty(), "identifier must not be empty");
                Eegeo_ASSERT(!title.empty(), "name must not be empty");
                Eegeo_ASSERT(!vendor.empty(), "vendor must not be empty");
            }
            
            SearchResultModel::~SearchResultModel()
            {
                
            }
            
            int SearchResultModel::GetVersion() const
            {
                return m_version;
            }
            
            const std::string& SearchResultModel::GetTitle() const
            {
                return m_title;
            }
            
            const std::string& SearchResultModel::GetIdentifier() const
            {
                return m_identifier;
            }
            
            const Eegeo::Space::LatLong& SearchResultModel::GetLocation() const
            {
                return m_location;
            }
            
            float SearchResultModel::GetHeightAboveTerrainMetres() const
            {
                return m_heightAboveTerrainMetres;
            }
            
            bool SearchResultModel::IsInterior() const
            {
                return m_interior;
            }
            
            const Eegeo::Resources::Interiors::InteriorId& SearchResultModel::GetBuildingId() const
            {
                return m_building;
            }
            
            int SearchResultModel::GetFloor() const
            {
                return m_floor;
            }
            
            const std::string& SearchResultModel::GetSubtitle() const
            {
                return m_subtitle;
            }
            
            const std::string& SearchResultModel::GetJsonData() const
            {
                return m_jsonData;
            }
            
            const std::vector<std::string>& SearchResultModel::GetHumanReadableTags() const
            {
                return m_humanReadableTags;
            }
            
            const std::string& SearchResultModel::GetVendor() const
            {
                return m_vendor;
            }
            
            int64_t SearchResultModel::GetCreationTimestamp() const
            {
                return m_searchResultCreationTimeStamp;
            }

            const TagIconKey& SearchResultModel::GetIconKey() const
            {
                return m_iconKey;
            }

            const std::vector<std::string>& SearchResultModel::GetTags() const
            {
                return m_tags;
            }

            std::string SearchResultModel::GetPrimaryTag() const
            {
                return m_tags.empty() ? "" : m_tags.front();
            }

            const bool operator< (const SearchResultModel& a, const SearchResultModel& b)
            {
                if(a.GetTitle() < b.GetTitle())
                {
                    return true;
                }
                else if (a.GetTitle() == b.GetTitle() && a.GetSubtitle() < b.GetSubtitle())
                {
                    return true;
                }
                else if (a.GetTitle() == b.GetTitle() && a.GetSubtitle() == b.GetSubtitle() && a.GetIdentifier() < b.GetIdentifier())
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            
            const bool operator== (const SearchResultModel& a, const SearchResultModel& b)
            {
                return (a.GetTitle() == b.GetTitle() && a.GetSubtitle() == b.GetSubtitle() && a.GetIdentifier() == b.GetIdentifier());
            }
        }
    }
}
