// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "iOSYelpSearchServiceModule.h"

#include <map>
#include <string>
#include "YelpSearchJsonParser.h"
#include "YelpSearchService.h"
#include "YelpSearchConstants.h"
#include "YelpCategoryMapper.h"
#include "iOSYelpSearchQueryFactory.h"
#include "ApiKey.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            iOSYelpSearchServiceModule::iOSYelpSearchServiceModule(Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                                                                   Net::SdkModel::INetworkCapabilities& networkCapabilities,
                                                                   Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder)
            {
                m_pYelpCategoryMapper = Eegeo_NEW(SdkModel::YelpCategoryMapper)(webRequestFactory,
                                                                            Yelp::SearchConstants::GetYelpFoundationCategoryToApplicationCategoryMap(),
                                                                            Yelp::SearchConstants::GetDefaultCategory());
                
                m_pSearchResultParser = Eegeo_NEW(SdkModel::YelpSearchJsonParser)(*m_pYelpCategoryMapper);
                
                m_pSearchQueryFactory = Eegeo_NEW(Yelp::iOSYelpSearchQueryFactory)(ExampleApp::YelpConsumerKey,
                                                                                   ExampleApp::YelpConsumerSecret,
                                                                                   ExampleApp::YelpOAuthToken,
                                                                                   ExampleApp::YelpOAuthTokenSecret,
                                                                                   *m_pYelpCategoryMapper);
                
                std::vector<std::string> categories = Yelp::SearchConstants::GetCategories();
                
                m_pSearchService = Eegeo_NEW(SdkModel::YelpSearchService)(*m_pSearchQueryFactory,
                                                                      *m_pSearchResultParser,
                                                                      networkCapabilities,
                                                                      categories);
            }
            
            iOSYelpSearchServiceModule::~iOSYelpSearchServiceModule()
            {
                Eegeo_DELETE m_pSearchService;
                Eegeo_DELETE m_pSearchQueryFactory;
                Eegeo_DELETE m_pSearchResultParser;
                Eegeo_DELETE m_pYelpCategoryMapper;
            }
            
            Search::SdkModel::ISearchService& iOSYelpSearchServiceModule::GetSearchService() const
            {
                return *m_pSearchService;
            }
            
            std::vector<CategorySearch::View::CategorySearchModel> iOSYelpSearchServiceModule::GetCategorySearchModels() const
            {
                return Yelp::SearchConstants::GetCategorySearchModels();
            }
        }
    }
}