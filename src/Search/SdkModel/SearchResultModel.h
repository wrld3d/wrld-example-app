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
            typedef std::string TagIconKey;

            class SearchResultModel
            {
                int m_version;
                std::string m_identifier;
                std::string m_title;
                std::string m_subtitle;
                Eegeo::Space::LatLong m_location;
                float m_heightAboveTerrainMetres;
                bool m_interior;
                Eegeo::Resources::Interiors::InteriorId m_building;
                int m_floor;
                std::vector<std::string> m_tags;
                std::vector<std::string> m_humanReadableTags;
                TagIconKey m_iconKey;
                std::string m_vendor;
                std::string m_jsonData;
                int64_t m_searchResultCreationTimeStamp;
                
            public:
                static const int CurrentVersion;
                
                SearchResultModel(int version,
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
                
                const std::string& GetSubtitle() const;
                
                const std::string& GetJsonData() const;

                const TagIconKey& GetIconKey() const;

                const std::vector<std::string>& GetTags() const;

                std::string GetPrimaryTag() const;

                const std::vector<std::string>& GetHumanReadableTags() const;
                
                const std::string& GetVendor() const;
                
                int64_t GetCreationTimestamp() const;
            };
            
            const bool operator< (const SearchResultModel& a, const SearchResultModel& b);
            
            const bool operator== (const SearchResultModel& a, const SearchResultModel& b);
            
            std::string SerializeToJson(const SearchResultModel& searchResult);
            
            bool TryDeserializeFromJson(const std::string& searchResultJson, SearchResultModel& out_resultModel);
        }
    }
}
