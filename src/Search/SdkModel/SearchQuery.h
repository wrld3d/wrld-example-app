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
            class SearchQuery
            {
                std::string m_query;
                bool m_isTag;
                bool m_tryInteriorSearch;
                Eegeo::Space::LatLongAltitude m_where;
                float m_radius;

            public:
                SearchQuery(const std::string& query,
                            bool isTag,
                            bool tryInteriorSearch,
                            const Eegeo::Space::LatLongAltitude& where,
                            float radius);

                ~SearchQuery();

                const std::string& Query() const;

                bool IsTag() const;
                
                bool ShouldTryInteriorSearch() const;

                float Radius() const;

                const Eegeo::Space::LatLongAltitude& Location() const;

            };
        }
    }
}
