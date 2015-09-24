// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidYelpSearchQueryFactory.h"
#include "AndroidYelpSearchQuery.h"
#include "AndroidYelpBusinessQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
        	AndroidYelpSearchQueryFactory::AndroidYelpSearchQueryFactory(
            		AndroidNativeState& nativeState,
        			const std::string& yelpConsumerKey,
        			const std::string& yelpConsumerSecret,
        			const std::string& yelpOAuthToken,
        			const std::string& yelpOAuthTokenSecret,
					SdkModel::IYelpCategoryMapper& yelpCategoryMapper)
            : m_nativeState(nativeState)
            , m_yelpConsumerKey(yelpConsumerKey)
            , m_yelpConsumerSecret(yelpConsumerSecret)
            , m_yelpOAuthToken(yelpOAuthToken)
            , m_yelpOAuthTokenSecret(yelpOAuthTokenSecret)
        	, m_yelpCategoryMapper(yelpCategoryMapper)
            {
            }
            
            AndroidYelpSearchQueryFactory::~AndroidYelpSearchQueryFactory()
            {
            }

            SdkModel::IYelpSearchQuery* AndroidYelpSearchQueryFactory::CreateYelpSearchForQuery(const Search::SdkModel::SearchQuery &query,
                                                                               Eegeo::Helpers::ICallback0 &completionCallback)

            {
                return Eegeo_NEW(AndroidYelpSearchQuery)(
                		m_nativeState,
                		m_yelpConsumerKey,
                		m_yelpConsumerSecret,
                		m_yelpOAuthToken,
                		m_yelpOAuthTokenSecret,
                		query,
                		completionCallback);
            }

            SdkModel::IYelpSearchQuery* AndroidYelpSearchQueryFactory::CreateYelpSearchForSpecificLocation(
            		const Search::SdkModel::SearchResultModel& outdatedSearchResult,
            		Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback)
            {
                return Eegeo_NEW(AndroidYelpBusinessQuery)(
                		m_nativeState,
                		m_yelpConsumerKey,
                		m_yelpConsumerSecret,
                		m_yelpOAuthToken,
                		m_yelpOAuthTokenSecret,
                		m_yelpCategoryMapper,
						outdatedSearchResult,
                		callback);
            }
        }
    }
}

