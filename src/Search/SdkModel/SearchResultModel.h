// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            class SearchResultModel
            {
                std::string m_identifier;
                std::string m_title;
                Eegeo::Space::LatLong m_location;
                std::string m_phone;
                std::string m_address;
                std::string m_webUrl;
                std::string m_category;
                std::string m_vicinity;

            public:
                SearchResultModel(const std::string& identifier,
                                  const std::string& title,
                                  const Eegeo::Space::LatLong& location,
                                  const std::string& phone,
                                  const std::string& address,
                                  const std::string& webUrl,
                                  const std::string& category,
                                  const std::string& vicinity);

                ~SearchResultModel();

                const std::string& GetTitle() const;

                const std::string& GetIdentifier() const;

                const Eegeo::Space::LatLong& GetLocation() const;

                const std::string& GetPhone() const;

                const std::string& GetAddress() const;

                const std::string& GetWebUrl() const;

                const std::string& GetCategory() const;

                const std::string& GetVicinity() const;
            };

            const bool operator< (const SearchResultModel& a, const SearchResultModel& b);
        }
    }
}
