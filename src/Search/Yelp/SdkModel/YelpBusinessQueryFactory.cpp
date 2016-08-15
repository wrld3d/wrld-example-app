// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "YelpBusinessQueryFactory.h"
#include "IdentitySearchCallbackData.h"
#include "YelpBusinessQuery.h"

#include <sstream>

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                YelpBusinessQueryFactory::YelpBusinessQueryFactory(
                                                               const std::string& yelpConsumerKey,
                                                               const std::string& yelpConsumerSecret,
                                                               const std::string& yelpOAuthToken,
                                                               const std::string& yelpOAuthTokenSecret,
                                                               const YelpBusinessJsonParser& yelpBusinessParser,
                                                               Eegeo::Web::IWebLoadRequestFactory& webRequestFactory)
                : m_yelpBusinessParser(yelpBusinessParser)
                , m_webRequestFactory(webRequestFactory)
                , m_consumer(yelpConsumerKey, yelpConsumerSecret)
                , m_token(yelpOAuthToken, yelpOAuthTokenSecret)
                , m_client(&m_consumer, &m_token)
                , m_apiUrl("https://api.yelp.com/v2/business/")
                {
                }

                
                SdkModel::YelpBusinessQuery* YelpBusinessQueryFactory::Create(const std::string& searchEntityId,
                                                                              Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& completionCallback)
                {
                    std::stringstream ss;
                    ss << m_apiUrl << searchEntityId << "?";
                    
                    const std::string& oauthParams = m_client.getURLQueryString(OAuth::Http::RequestType::Get, ss.str());

                    ss << oauthParams;
                    
                    return Eegeo_NEW(YelpBusinessQuery)(ss.str(), completionCallback, m_webRequestFactory, m_yelpBusinessParser);
                }
            }
        }
    }
}