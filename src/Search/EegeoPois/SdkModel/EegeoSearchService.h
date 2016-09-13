// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "SearchServiceBase.h"

#include "EegeoPois.h"
#include "NetIncludes.h"
#include "SearchQuery.h"

#include <vector>
#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class EegeoSearchService : public Search::SdkModel::SearchServiceBase, private Eegeo::NonCopyable
                {
                private:
                    std::shared_ptr<IEegeoSearchQueryFactory> m_eeGeoSearchQueryFactory;
                    std::shared_ptr<IEegeoParser> m_eeGeoParser;
                    std::shared_ptr<Net::SdkModel::INetworkCapabilities> m_networkCapabilities;
                    Search::SdkModel::SearchQuery m_currentQueryModel;
                    Eegeo::Helpers::TCallback0<EegeoSearchService> m_searchCallback;
                    IEegeoSearchQuery* m_pCurrentRequest;
                    bool m_hasActiveQuery;
                    Eegeo::Helpers::TCallback0<EegeoSearchService> m_networkCapabilitiesChangedHandler;
                    
                public:
                    EegeoSearchService(const std::shared_ptr<IEegeoSearchQueryFactory>& EegeoSearchQueryFactory,
                                       const std::shared_ptr<IEegeoParser>& EegeoParser,
                                       const std::shared_ptr<Net::SdkModel::INetworkCapabilities>& networkCapabilities,
                                       const std::vector<std::string>& handledTags);
                    
                    ~EegeoSearchService();
                    
                    bool CanHandleIndoor() const { return true; }

                    void CancelInFlightQueries();
                    
                    void PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query);
                    
                    void PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                               Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback);
                    
                private:
                    void HandleSearchResponse();
                    void HandleNetworkCapabilitiesChanged();
                };
            }
        }
    }
}