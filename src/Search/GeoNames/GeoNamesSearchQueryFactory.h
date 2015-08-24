// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "Types.h"
#include "IGeoNamesSearchQueryFactory.h"
#include "IGeoNamesSearchQuery.h"
#include "Web.h"
#include "UrlHelpers.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            class GeoNamesSearchQueryFactory : public IGeoNamesSearchQueryFactory, private Eegeo::NonCopyable
            {
                std::string m_geoNamesUserName;
                Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                Eegeo::Helpers::UrlHelpers::IUrlEncoder& m_urlEncoder;
                
            public:
                GeoNamesSearchQueryFactory(const std::string& geoNamesUserName,
                                           Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                           Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder);
                
                ~GeoNamesSearchQueryFactory();
                
                IGeoNamesSearchQuery* CreateGeoNamesSearchForQuery(const SdkModel::SearchQuery& query,
                                                                   Eegeo::Helpers::ICallback0& completionCallback);
            };
        }
    }
}
