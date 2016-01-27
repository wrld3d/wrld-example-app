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
            namespace SdkModel
            {
                class GeoNamesSearchResultDto
                {
                    std::string m_id;
                    std::string m_name;
                    std::string m_country;
                    Eegeo::Space::LatLong m_location;
                    
                public:
                    GeoNamesSearchResultDto(const std::string& id,
                                            const std::string& name,
                                            const std::string& country,
                                            const Eegeo::Space::LatLong& location,
                                            int population);
                    
                    Search::SdkModel::SearchResultModel ToSearchResultModel() const;
                };
            }
        }
    }
}
