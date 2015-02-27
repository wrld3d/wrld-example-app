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

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            class iOSYelpSearchServiceModule : public SdkModel::ISearchServiceModule, private Eegeo::NonCopyable
            {
                SdkModel::ISearchService* m_pSearchService;
                Yelp::IYelpSearchQueryFactory* m_pSearchQueryFactory;
                Yelp::IYelpCategoryMapper* m_pYelpCategoryMapper;
                SdkModel::ISearchResultParser* m_pSearchResultParser;
                GeoNames::IGeoNamesSearchQueryFactory* m_pGeoNamesSearchQueryFactory;
                GeoNames::IGeoNamesParser* m_pGeoNamesParser;
                
            public:
                iOSYelpSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                           Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                           Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder);
                
                ~iOSYelpSearchServiceModule();
                
                SdkModel::ISearchService& GetSearchService() const;
                
                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels() const;
            };
        }
    }
}

