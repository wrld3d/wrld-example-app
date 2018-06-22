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
                                                               const std::string& yelpApiKey,
                                                               const YelpBusinessJsonParser& yelpBusinessParser,
                                                               Eegeo::Web::IWebLoadRequestFactory& webRequestFactory)
                : m_yelpBusinessParser(yelpBusinessParser)
                , m_webRequestFactory(webRequestFactory)
                , m_yelpApiKey(yelpApiKey)
                , m_apiUrl("https://api.yelp.com/v3/businesses/")
                {
                }

                
                SdkModel::YelpBusinessQuery* YelpBusinessQueryFactory::Create(const std::string& searchEntityId,
                                                                              Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& completionCallback)
                {
                    std::stringstream ss;
                    ss << m_apiUrl << searchEntityId << "?";
                    
                    return Eegeo_NEW(YelpBusinessQuery)(ss.str(), m_yelpApiKey, completionCallback, m_webRequestFactory, m_yelpBusinessParser);
                }
            }
        }
    }
}