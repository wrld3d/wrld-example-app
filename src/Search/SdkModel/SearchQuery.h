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
                bool m_selectFirstResult;
                Eegeo::Space::LatLongAltitude m_where;
                float m_radius;
                std::string m_interiorId;

            public:
                SearchQuery();
                SearchQuery(const std::string& query,
                            bool isTag,
                            bool tryInteriorSearch,
                            bool selectFirstResult,
                            const Eegeo::Space::LatLongAltitude& where,
                            float radius,
                            const std::string& interiorId = "");

                ~SearchQuery();

                const std::string& Query() const;

                bool IsTag() const;
                
                bool ShouldTryInteriorSearch() const;

                bool SelectFirstResult() const;

                float Radius() const;

                const Eegeo::Space::LatLongAltitude& Location() const;
                
                const std::string& InteriorId() const;
            };
        }
    }
}
