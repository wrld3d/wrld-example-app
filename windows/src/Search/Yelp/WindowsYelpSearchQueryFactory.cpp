// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WindowsYelpSearchQueryFactory.h"
#include "WindowsYelpSearchQuery.h"
#include "WindowsYelpBusinessQuery.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            WindowsYelpSearchQueryFactory::WindowsYelpSearchQueryFactory(
                WindowsNativeState& nativeState,
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

            WindowsYelpSearchQueryFactory::~WindowsYelpSearchQueryFactory()
            {
            }

            SdkModel::IYelpSearchQuery* WindowsYelpSearchQueryFactory::CreateYelpSearchForQuery(const Search::SdkModel::SearchQuery &query,
                Eegeo::Helpers::ICallback0 &completionCallback)

            {
                return Eegeo_NEW(WindowsYelpSearchQuery)(
                    m_nativeState,
                    m_yelpConsumerKey,
                    m_yelpConsumerSecret,
                    m_yelpOAuthToken,
                    m_yelpOAuthTokenSecret,
                    query,
                    completionCallback);
            }

            SdkModel::IYelpSearchQuery* WindowsYelpSearchQueryFactory::CreateYelpSearchForSpecificLocation(
                const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback)
            {
                return Eegeo_NEW(WindowsYelpBusinessQuery)(
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
