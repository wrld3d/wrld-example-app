// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"
#include "Types.h"
#include "IGeoNamesSearchQueryFactory.h"
#include "IGeoNamesSearchQuery.h"
#include "Web.h"
#include "ApplicationConfiguration.h"
#include "UrlHelpers.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                class GeoNamesSearchQueryFactory : public IGeoNamesSearchQueryFactory, private Eegeo::NonCopyable
                {
                    std::shared_ptr<Eegeo::Web::IWebLoadRequestFactory> m_webRequestFactory;
                    std::shared_ptr<Eegeo::Helpers::UrlHelpers::IUrlEncoder> m_urlEncoder;
                    
                    std::string m_geoNamesUserName;
                    
                public:
                    GeoNamesSearchQueryFactory(const std::shared_ptr<Eegeo::Web::IWebLoadRequestFactory>& webRequestFactory,
                                               const std::shared_ptr<Eegeo::Helpers::UrlHelpers::IUrlEncoder>& urlEncoder,
                                               const std::shared_ptr<ExampleApp::ApplicationConfig::ApplicationConfiguration>& config);
                    
                    ~GeoNamesSearchQueryFactory();
                    
                    IGeoNamesSearchQuery* CreateGeoNamesSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                                       Eegeo::Helpers::ICallback0& completionCallback);
                };
            }
        }
    }
}
