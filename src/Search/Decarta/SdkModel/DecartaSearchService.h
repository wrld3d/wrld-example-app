// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <sstream>
#include "Search.h"
#include "SearchServiceBase.h"
#include "Types.h"
#include "Web.h"
#include "UrlHelpers.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Decarta
        {
            namespace SdkModel
            {
                class DecartaSearchService : public Search::SdkModel::SearchServiceBase, private Eegeo::NonCopyable
                {
                private:
                    std::string m_decartaApiKey;
                    Search::SdkModel::ISearchResultParser& m_parser;
                    Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                    Eegeo::Helpers::UrlHelpers::IUrlEncoder& m_urlEncoder;
                    Eegeo::Web::IWebLoadRequestCompletionCallback* m_pPoiSearchCallback;
                    Eegeo::Web::IWebLoadRequest* m_pCurrentRequest;

                public:
                    DecartaSearchService(const std::string& decartaApiKey,
                                         Search::SdkModel::ISearchResultParser& parser,
                                         Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                         Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                         const std::vector<std::string>& availableCategories);

                    ~DecartaSearchService();

                    void CancelInFlightQueries();

                    void PerformLocationQuerySearch(const Search::SdkModel::SearchQuery& query);
                    
                    void PerformIdentitySearch(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                               Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback);

                private:

                    void IssueRequest(const std::string queryUrl, const Search::SdkModel::SearchQuery& query);

                    void HandleSearchResponse(Eegeo::Web::IWebLoadRequest& webLoadRequest);

                    void EncodeApiQueryIntoStringStream(const std::string& query,
                                                        const std::string& apiPoint,
                                                        std::stringstream& out_stream);
                };
            }
        }
    }
}

