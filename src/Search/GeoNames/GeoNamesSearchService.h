// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "SearchServiceBase.h"

#include "GeoNames.h"
#include "NetIncludes.h"
#include "SearchQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            class GeoNamesSearchService : public SdkModel::SearchServiceBase, private Eegeo::NonCopyable
            {
            private:
                GeoNames::IGeoNamesSearchQueryFactory& m_geoNamesSearchQueryFactory;
                GeoNames::IGeoNamesParser& m_geoNamesParser;
                Net::SdkModel::INetworkCapabilities& m_networkCapabilities;
                SdkModel::SearchQuery m_currentQueryModel;
                Eegeo::Helpers::TCallback0<GeoNamesSearchService> m_searchCallback;
                GeoNames::IGeoNamesSearchQuery* m_pCurrentRequest;
                bool m_hasActiveQuery;
                
            public:
                GeoNamesSearchService(IGeoNamesSearchQueryFactory& geoNamesSearchQueryFactory,
                                      IGeoNamesParser& geoNamesParser,
                                      Net::SdkModel::INetworkCapabilities& networkCapabilities);
                
                ~GeoNamesSearchService();
                
                void CancelInFlightQueries();
                
                void PerformLocationQuerySearch(const SdkModel::SearchQuery& query);
                
                void PerformIdentitySearch(const SdkModel::SearchResultModel& outdatedSearchResult,
                                           Eegeo::Helpers::ICallback1<const SdkModel::IdentitySearchCallbackData&>& callback);
                
            private:
                void HandleSearchResponse();
            };
        }
    }
}