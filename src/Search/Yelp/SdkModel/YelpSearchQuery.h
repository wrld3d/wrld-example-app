// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "IYelpSearchQuery.h"
#include "Types.h"
#include "SearchQuery.h"
#include "ICallback.h"
#include "Yelp.h"
#include "IWebLoadRequestFactory.h"
#include "WebLoadRequestCompletionCallback.h"

#include "liboauthcpp.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                class YelpSearchQuery : public SdkModel::IYelpSearchQuery, private Eegeo::NonCopyable
                {
                public:
                    YelpSearchQuery(
                        const std::string& yelpConsumerKey,
                        const std::string& yelpConsumerSecret,
                        const std::string& yelpOAuthToken,
                        const std::string& yelpOAuthTokenSecret,
                        const Search::SdkModel::SearchQuery& searchQuery,
                        Eegeo::Helpers::ICallback0& completionCallback,
                        Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                        bool enableSSL = false);

                    ~YelpSearchQuery();

                    void Dispatch();

                    void Cancel();

                    void HandleQueryCompleted(const std::string& queryString, bool success);

                    bool IsSucceeded();

                    const std::string& ResponseString();

                    const Search::SdkModel::SearchQuery& GetSearchQuery() const;

                private:
                    const float MaxRadiusMetres;

                    const Search::SdkModel::SearchQuery& m_searchQuery;
                    Eegeo::Helpers::ICallback0& m_completionCallback;
                    std::string m_responseString;
                    bool m_cancelled;
                    bool m_dispatched;
                    bool m_isSuccess;
                    bool m_enableSSL;

                    Eegeo::Web::TWebLoadRequestCompletionCallback<YelpSearchQuery> m_webRequestCompleteCallback;
                    void HandleWebResponseComplete(Eegeo::Web::IWebResponse& webResponse);

                    Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;

                    const std::string& m_yelpConsumerKey;
                    const std::string& m_yelpConsumerSecret;
                    const std::string& m_yelpOAuthToken;
                    const std::string& m_yelpOAuthTokenSecret;

                    OAuth::Consumer m_consumer;
                    OAuth::Client m_client;
                    OAuth::Token m_token;

                    const std::string m_apiUrl;
                    const std::string m_apiUrlSecure;
                    const std::string m_searchPath;
                    const std::string m_searchLimit;
                };
            }
        }
    }
}
