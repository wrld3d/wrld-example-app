// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "SearchResultModel.h"
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            class GeoNamesSearchResultDto
            {
                std::string m_name;
                std::string m_country;
                Eegeo::Space::LatLong m_location;
                int m_population;
                
            public:
                GeoNamesSearchResultDto(const std::string& name,
                                        const std::string& country,
                                        const Eegeo::Space::LatLong& location,
                                        int population);
                
                SdkModel::SearchResultModel ToSearchResultModel() const;
            };
        }
    }
}
