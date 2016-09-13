// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            SearchQuery::SearchQuery(const std::string& query,
                                     bool isTag,
                                     bool tryInteriorSearch,
                                     const Eegeo::Space::LatLongAltitude& where,
                                     float radius)
                : m_query(query)
                , m_isTag(isTag)
                , m_tryInteriorSearch(tryInteriorSearch)
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

            bool SearchQuery::IsTag() const
            {
                return m_isTag;
            }
            
            bool SearchQuery::ShouldTryInteriorSearch() const
            {
                return m_tryInteriorSearch;
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
