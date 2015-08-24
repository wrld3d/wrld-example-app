// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <map>
#include <string>
#include "iOSYelpSearchServiceModule.h"
#include "YelpSearchJsonParser.h"
#include "YelpSearchService.h"
#include "YelpSearchConstants.h"
#include "YelpCategoryMapper.h"
#include "iOSYelpSearchQueryFactory.h"
#include "GeoNamesSearchQueryFactory.h"
#include "GeoNamesJsonParser.h"
#include "ApiKey.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            iOSYelpSearchServiceModule::iOSYelpSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                   Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                                   Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                                                                   const std::string& yelpConsumerKey,
                                                                   const std::string& yelpConsumerSecret,
                                                                   const std::string& yelpOAuthToken,
                                                                   const std::string& yelpOAuthTokenSecret,
                                                                   const std::string& geoNamesUserName)
            {
                m_pYelpCategoryMapper = Eegeo_NEW(Yelp::YelpCategoryMapper)(webRequestFactory,
                                                                            Yelp::GetYelpFoundationCategoryToApplicationCategoryMap(),
                                                                            Yelp::GetDefaultCategory());
                
                m_pSearchResultParser = Eegeo_NEW(Yelp::YelpSearchJsonParser)(*m_pYelpCategoryMapper);
                
                m_pSearchQueryFactory = Eegeo_NEW(Yelp::iOSYelpSearchQueryFactory)(yelpConsumerKey,
                                                                                   yelpConsumerSecret,
                                                                                   yelpOAuthToken,
                                                                                   yelpOAuthTokenSecret,
                                                                                   *m_pYelpCategoryMapper);

                m_pGeoNamesSearchQueryFactory = Eegeo_NEW(GeoNames::GeoNamesSearchQueryFactory)(geoNamesUserName,
                                                                                                webRequestFactory,
                                                                                                urlEncoder);
                m_pGeoNamesParser = Eegeo_NEW(GeoNames::GeoNamesJsonParser)();
                
                m_pSearchService = Eegeo_NEW(Yelp::YelpSearchService)(*m_pSearchQueryFactory,
                                                                      *m_pSearchResultParser,
                                                                      *m_pGeoNamesSearchQueryFactory,
                                                                      *m_pGeoNamesParser,
                                                                      networkCapabilities);
            }
            
            iOSYelpSearchServiceModule::~iOSYelpSearchServiceModule()
            {
                Eegeo_DELETE m_pSearchService;
                Eegeo_DELETE m_pGeoNamesParser;
                Eegeo_DELETE m_pGeoNamesSearchQueryFactory;
                Eegeo_DELETE m_pSearchQueryFactory;
                Eegeo_DELETE m_pSearchResultParser;
                Eegeo_DELETE m_pYelpCategoryMapper;
            }
            
            SdkModel::ISearchService& iOSYelpSearchServiceModule::GetSearchService() const
            {
                return *m_pSearchService;
            }
            
            std::vector<CategorySearch::View::CategorySearchModel> iOSYelpSearchServiceModule::GetCategorySearchModels() const
            {
                return Yelp::GetCategorySearchModels();
            }
        }
    }
}