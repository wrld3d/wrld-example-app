// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "InteriorId.h"
#include "LatLongAltitude.h"
#include "Types.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            class SearchResultModel
            {
                int m_version;
                std::string m_identifier;
                std::string m_title;
                Eegeo::Space::LatLong m_location;
                float m_heightAboveTerrainMetres;
                bool m_interior;
                Eegeo::Resources::Interiors::InteriorId m_building;
                int m_floor;
                std::string m_phone;
                std::string m_address;
                std::string m_webUrl;
                std::string m_applicationCategory;
                std::vector<std::string> m_humanReadableCategories;
                std::string m_vicinity;
                std::string m_vendor;
                std::string m_imageUrl;
                std::string m_ratingImageUrl;
                std::vector<std::string> m_reviews;
                int m_reviewCount;
                int64_t m_searchResultCreationTimeStamp;
                
            public:
                static const int CurrentVersion;
                
                SearchResultModel(int version,
                                  const std::string& identifier,
                                  const std::string& title,
                                  const Eegeo::Space::LatLong& location,
                                  float heightAboveTerrainMetres,
                                  bool interior,
                                  const Eegeo::Resources::Interiors::InteriorId& building,
                                  int floor,
                                  const std::string& phone,
                                  const std::string& address,
                                  const std::string& webUrl,
                                  const std::string& applicationCategory,
                                  const std::vector<std::string>& humanReadableCategories,
                                  const std::string& vicinity,
                                  const std::string& vendor,
                                  const std::string& imageUrl,
                                  const std::string& ratingImageUrl,
                                  const std::vector<std::string>& reviews,
                                  int reviewCount,
                                  int64_t searchResultCreationTimeStamp);
                
                SearchResultModel();

                ~SearchResultModel();
                
                int GetVersion() const;
                
                const std::string& GetTitle() const;

                const std::string& GetIdentifier() const;

                const Eegeo::Space::LatLong& GetLocation() const;
                
                float GetHeightAboveTerrainMetres() const;
                
                bool IsInterior() const;
                
                const Eegeo::Resources::Interiors::InteriorId& GetBuildingId() const;
                
                int GetFloor() const;

                const std::string& GetPhone() const;

                const std::string& GetAddress() const;

                const std::string& GetWebUrl() const;

                const std::string& GetCategory() const;
                
                const std::vector<std::string>& GetHumanReadableCategories() const;

                const std::string& GetVicinity() const;
                
                const std::string& GetVendor() const;
                
                bool HasImage() const;
                
                const std::string& GetImageUrl() const;
                
                bool HasRatingImage() const;
                
                const std::string& GetRatingImageUrl() const;
                
                const std::vector<std::string>& GetReviews() const;
                
                const int GetReviewCount() const;
                
                int64_t GetCreationTimestamp() const;
            };

            const bool operator< (const SearchResultModel& a, const SearchResultModel& b);
            
            const bool operator== (const SearchResultModel& a, const SearchResultModel& b);
            
            std::string SerializeToJson(const SearchResultModel& searchResult);
            
            SearchResultModel DeserializeFromJson(const std::string& searchResultJson);
        }
    }
}
