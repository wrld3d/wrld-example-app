// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            SearchQuery::SearchQuery()
            : m_query("")
            , m_isTag(false)
            , m_tryInteriorSearch(false)
            , m_selectFirstResult(false)
            , m_where(0, 0, 0)
            , m_radius(0.f)
            , m_interiorId("")
            {
            }

            SearchQuery::SearchQuery(const std::string& query,
                                     bool isTag,
                                     bool tryInteriorSearch,
									 bool selectFirstResult,
                                     const Eegeo::Space::LatLongAltitude& where,
                                     float radius,
                                     const std::string& interiorId)
                : m_query(query)
                , m_isTag(isTag)
                , m_tryInteriorSearch(tryInteriorSearch)
                , m_selectFirstResult(selectFirstResult)
                , m_where(where)
                , m_radius(radius)
                , m_interiorId(interiorId)
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

            bool SearchQuery::SelectFirstResult() const
            {
                return m_selectFirstResult;
            }

            float SearchQuery::Radius() const
            {
                return m_radius;
            }

            const Eegeo::Space::LatLongAltitude& SearchQuery::Location() const
            {
                return m_where;
            }
            
            const std::string& SearchQuery::InteriorId() const
            {
                return m_interiorId;
            }
        }
    }
}
