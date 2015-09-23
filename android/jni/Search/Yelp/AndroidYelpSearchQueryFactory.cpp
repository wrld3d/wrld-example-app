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
                    IYelpCategoryMapper& yelpCategoryMapper)
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

            IYelpSearchQuery* AndroidYelpSearchQueryFactory::CreateYelpSearchForQuery(const SdkModel::SearchQuery &query,
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

            IYelpSearchQuery* AndroidYelpSearchQueryFactory::CreateYelpSearchForSpecificLocation(
            		const SdkModel::SearchResultModel& outdatedSearchResult,
            		Eegeo::Helpers::ICallback1<const SdkModel::IdentitySearchCallbackData&>& callback)
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

