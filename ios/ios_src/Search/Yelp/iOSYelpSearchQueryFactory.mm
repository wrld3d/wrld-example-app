// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "iOSYelpSearchQueryFactory.h"
#include "iOSYelpSearchQuery.h"
#include "iOSYelpBusinessQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            iOSYelpSearchQueryFactory::iOSYelpSearchQueryFactory(const std::string& yelpConsumerKey,
                                                                 const std::string& yelpConsumerSecret,
                                                                 const std::string& yelpOAuthToken,
                                                                 const std::string& yelpOAuthTokenSecret,
                                                                 IYelpCategoryMapper& yelpCategoryMapper)
            : m_yelpConsumerKey(yelpConsumerKey)
            , m_yelpConsumerSecret(yelpConsumerSecret)
            , m_yelpOAuthToken(yelpOAuthToken)
            , m_yelpOAuthTokenSecret(yelpOAuthTokenSecret)
            , m_yelpCategoryMapper(yelpCategoryMapper)
            {
            }
            
            iOSYelpSearchQueryFactory::~iOSYelpSearchQueryFactory()
            {
            }
            
            IYelpSearchQuery* iOSYelpSearchQueryFactory::CreateYelpSearchForQuery(const SdkModel::SearchQuery& query,
                                                                                  Eegeo::Helpers::ICallback0& completionCallback,
                                                                                  SdkModel::ISearchResultParser& m_searchResultParser)
            
            {
                return Eegeo_NEW(iOSYelpSearchQuery)(m_yelpConsumerKey,
                                                     m_yelpConsumerSecret,
                                                     m_yelpOAuthToken,
                                                     m_yelpOAuthTokenSecret,
                                                     query,
                                                     completionCallback,
                                                     m_searchResultParser);
            }
            
            IYelpSearchQuery* iOSYelpSearchQueryFactory::CreateYelpSearchForSpecificLocation(const std::string& locationIdentifier,
                                                                                             Eegeo::Helpers::ICallback1<const SdkModel::IdentitySearchCallbackData&>& callback,
                                                                                             SdkModel::ISearchResultParser& m_searchResultParser)
            
            {
                return Eegeo_NEW(iOSYelpBusinessQuery)(m_yelpConsumerKey,
                                                       m_yelpConsumerSecret,
                                                       m_yelpOAuthToken,
                                                       m_yelpOAuthTokenSecret,
                                                       m_yelpCategoryMapper,
                                                       locationIdentifier,
                                                       callback,
                                                       m_searchResultParser);
            }
        }
    }
}

