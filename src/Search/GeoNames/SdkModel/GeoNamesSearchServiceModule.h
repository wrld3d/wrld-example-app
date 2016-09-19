// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchServiceModule.h"

#include "Types.h"
#include "UrlHelpers.h"
#include "Web.h"
#include "GeoNames.h"
#include "NetIncludes.h"
#include "Search.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                class GeoNamesSearchServiceModule : public Search::SdkModel::ISearchServiceModule, private Eegeo::NonCopyable
                {
                private:
                    IGeoNamesSearchQueryFactory* m_pGeoNamesSearchQueryFactory;
                    IGeoNamesParser* m_pGeoNamesParser;
                    Search::SdkModel::ISearchService* m_pSearchService;
                public:
                    GeoNamesSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                const std::string& geoNamesUserName);
                    
                    ~GeoNamesSearchServiceModule();
                    
                    Search::SdkModel::ISearchService& GetSearchService() const;
                };
            }
        }
    }
}