// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "LatLongAltitude.h"

namespace ExampleApp
{
    namespace Search
    {
        class SearchQuery
        {
            std::string m_query;
            bool m_isCategory;
            Eegeo::Space::LatLongAltitude m_where;
            float m_radius;
            
        public:
            SearchQuery(const std::string& query,
                        bool isCategory,
                        const Eegeo::Space::LatLongAltitude& where,
                        float radius);
            
            ~SearchQuery();
            
            const std::string& Query() const;
        
            bool IsCategory() const;
            
            float Radius() const;
            
            const Eegeo::Space::LatLongAltitude& Location() const;
            
        };
    }
}
