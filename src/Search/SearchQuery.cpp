// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        SearchQuery::SearchQuery(const std::string& query,
                                 bool isCategory,
                                 const Eegeo::Space::LatLongAltitude& where,
                                 float radius)
        : m_query(query)
        , m_isCategory(isCategory)
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
