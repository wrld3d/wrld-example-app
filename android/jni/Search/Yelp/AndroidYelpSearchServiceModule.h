// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Yelp.h"
#include "Search.h"
#include "GeoNames.h"
#include "Web.h"
#include "NetIncludes.h"
#include "UrlHelpers.h"
#include "ISearchServiceModule.h"
#include "AndroidNativeState.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            class AndroidYelpSearchServiceModule : public SdkModel::ISearchServiceModule, private Eegeo::NonCopyable
            {
                SdkModel::ISearchService* m_pSearchService;
                Yelp::IYelpSearchQueryFactory* m_pSearchQueryFactory;
                SdkModel::ISearchResultParser* m_pSearchResultParser;
                Yelp::IYelpCategoryMapper* m_pYelpCategoryMapper;
                GeoNames::IGeoNamesSearchQueryFactory* m_pGeoNamesSearchQueryFactory;
                GeoNames::IGeoNamesParser* m_pGeoNamesParser;
                
            public:
                AndroidYelpSearchServiceModule(AndroidNativeState& nativeState,
                		Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                        Net::SdkModel::INetworkCapabilities& networkCapabilities,
                        Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                        const std::string& yelpConsumerKey,
                        const std::string& yelpConsumerSecret,
                        const std::string& yelpOAuthToken,
                        const std::string& yelpOAuthTokenSecret,
                        const std::string& geoNamesUserName);
                
                ~AndroidYelpSearchServiceModule();
                
                SdkModel::ISearchService& GetSearchService() const;
                
                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels() const;
            };
        }
    }
}

