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
            GeoNamesSearchServiceModule::GeoNamesSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                     Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                                     Net::SdkModel::INetworkCapabilities& networkCapabilities)
            : m_pGeoNamesSearchQueryFactory(NULL)
            , m_pGeoNamesParser(NULL)
            , m_pSearchService(NULL)
            {
                m_pGeoNamesSearchQueryFactory = Eegeo_NEW(GeoNames::GeoNamesSearchQueryFactory)(webRequestFactory,
                                                                                                urlEncoder);
                m_pGeoNamesParser = Eegeo_NEW(GeoNames::GeoNamesJsonParser)();
                
                m_pSearchService = Eegeo_NEW(GeoNamesSearchService)(*m_pGeoNamesSearchQueryFactory,
                                                                    *m_pGeoNamesParser,
                                                                    networkCapabilities);
            }
            
            GeoNamesSearchServiceModule::~GeoNamesSearchServiceModule()
            {
                Eegeo_DELETE m_pSearchService;
            }
            
            SdkModel::ISearchService& GeoNamesSearchServiceModule::GetSearchService() const
            {
                return *m_pSearchService;
            }
            
            std::vector<CategorySearch::View::CategorySearchModel> GeoNamesSearchServiceModule::GetCategorySearchModels() const
            {
                return std::vector<CategorySearch::View::CategorySearchModel>();
            }
        }
    }
}
