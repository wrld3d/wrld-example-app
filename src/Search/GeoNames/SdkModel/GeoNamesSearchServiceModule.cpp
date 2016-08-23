// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GeoNamesSearchServiceModule.h"

#include "GeoNamesJsonParser.h"
#include "GeoNamesSearchQueryFactory.h"
#include "GeoNamesSearchService.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace GeoNames
        {
            namespace SdkModel
            {
                GeoNamesSearchServiceModule::GeoNamesSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                         Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                                         Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                                         const std::string& geoNamesUserName)
                : m_pGeoNamesSearchQueryFactory(NULL)
                , m_pGeoNamesParser(NULL)
                , m_pSearchService(NULL)
                {
                    m_pGeoNamesSearchQueryFactory = Eegeo_NEW(GeoNamesSearchQueryFactory)(webRequestFactory,
                                                                                          urlEncoder,
                                                                                          geoNamesUserName);
                    
                    m_pGeoNamesParser = Eegeo_NEW(GeoNamesJsonParser)();
                    
                    m_pSearchService = Eegeo_NEW(GeoNamesSearchService)(*m_pGeoNamesSearchQueryFactory,
                                                                        *m_pGeoNamesParser,
                                                                        networkCapabilities);
                }
                
                GeoNamesSearchServiceModule::~GeoNamesSearchServiceModule()
                {
                    Eegeo_DELETE m_pSearchService;
                }
                
                Search::SdkModel::ISearchService& GeoNamesSearchServiceModule::GetSearchService() const
                {
                    return *m_pSearchService;
                }
            }
        }
    }
}
