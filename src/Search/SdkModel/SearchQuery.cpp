// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            SearchQuery::SearchQuery(const std::string& query,
                                     bool isCategory,
                                     bool inInterior,
                                     const Eegeo::Space::LatLongAltitude& where,
                                     float radius)
                : m_query(query)
                , m_isCategory(isCategory)
                , m_isInterior(inInterior)
                , m_where(where)
                , m_radius(radius)
            {
            }

            SearchQuery::~SearchQuery()
            {

            }

            const std::string& SearchQuery::Query() const
            {
                return m_query;
            }

            bool SearchQuery::IsCategory() const
            {
                return m_isCategory;
            }
            
            bool SearchQuery::IsInterior() const
            {
                return m_isInterior;
            }

            float SearchQuery::Radius() const
            {
                return m_radius;
            }

            const Eegeo::Space::LatLongAltitude& SearchQuery::Location() const
            {
                return m_where;
            }
        }
    }
}
