// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Types.h"
#include "Yelp.h"
#include "Search.h"
#include "ICallback.h"
#include "IYelpSearchQueryFactory.h"
#include "AndroidNativeState.h"
#include "IdentitySearchCallbackData.h"
#include "IYelpCategoryMapper.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            class AndroidYelpSearchQueryFactory : public SdkModel::IYelpSearchQueryFactory, private Eegeo::NonCopyable
            {
        		AndroidNativeState& m_nativeState;
                std::string m_yelpConsumerKey;
                std::string m_yelpConsumerSecret;
                std::string m_yelpOAuthToken;
                std::string m_yelpOAuthTokenSecret;
                SdkModel::IYelpCategoryMapper& m_yelpCategoryMapper;
                
            public:
                AndroidYelpSearchQueryFactory(
                		AndroidNativeState& nativeState,
                		const std::string& yelpConsumerKey,
                		const std::string& yelpConsumerSecret,
                		const std::string& yelpOAuthToken,
                		const std::string& yelpOAuthTokenSecret,
						SdkModel::IYelpCategoryMapper& yelpCategoryMapper);
                
                ~AndroidYelpSearchQueryFactory();
                
                SdkModel::IYelpSearchQuery* CreateYelpSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                           Eegeo::Helpers::ICallback0& completionCallback);

                SdkModel::IYelpSearchQuery* CreateYelpSearchForSpecificLocation(const Search::SdkModel::SearchResultModel& outdatedSearchResult,
                                                                      Eegeo::Helpers::ICallback1<const Search::SdkModel::IdentitySearchCallbackData&>& callback);
            };
        }
    }
}
