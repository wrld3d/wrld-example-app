// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "YelpSearchServiceModule.h"
#include "YelpSearchJsonParser.h"
#include "YelpBusinessJsonParser.h"
#include "YelpSearchService.h"
#include "YelpCategoryMapper.h"
#include "YelpSearchConstants.h"
#include "ApiKey.h"
#include "YelpSearchQueryFactory.h"
#include "YelpBusinessQueryFactory.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            YelpSearchServiceModule::YelpSearchServiceModule(
                Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                Net::SdkModel::INetworkCapabilities& networkCapabilities,
                Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
				const std::string& yelpConsumerKey,
				const std::string& yelpConsumerSecret,
				const std::string& yelpOAuthToken,
				const std::string& yelpOAuthTokenSecret,
                Eegeo::Helpers::IFileIO& fileIO)
            : m_pSearchService(NULL)
            , m_pSearchQueryFactory(NULL)
            , m_pYelpBusinessQueryFactory(NULL)
            , m_pYelpSearchJsonParser(NULL)
            , m_pYelpBusinessJsonParser(NULL)
            , m_pYelpCategoryMapper(NULL)
            {
                m_pYelpCategoryMapper = Eegeo_NEW(Yelp::SdkModel::YelpCategoryMapper)(webRequestFactory,
                    Yelp::SearchConstants::GetYelpFoundationCategoryToApplicationCategoryMap(fileIO),
                    Yelp::SearchConstants::GetDefaultCategory());

                m_pYelpSearchJsonParser = Eegeo_NEW(Yelp::SdkModel::YelpSearchJsonParser)(*m_pYelpCategoryMapper);
                
                m_pYelpBusinessJsonParser = Eegeo_NEW(Yelp::SdkModel::YelpBusinessJsonParser)(*m_pYelpCategoryMapper);

                m_pSearchQueryFactory = Eegeo_NEW(Yelp::SdkModel::YelpSearchQueryFactory)(
                    yelpConsumerKey,
                    yelpConsumerSecret,
                    yelpOAuthToken,
                    yelpOAuthTokenSecret,
                    webRequestFactory);
                
                m_pYelpBusinessQueryFactory = Eegeo_NEW(Yelp::SdkModel::YelpBusinessQueryFactory)(
                                                                                                  yelpConsumerKey,
                                                                                                  yelpConsumerSecret,
                                                                                                  yelpOAuthToken,
                                                                                                  yelpOAuthTokenSecret,
                                                                                                  *m_pYelpBusinessJsonParser,
                                                                                                  webRequestFactory);

                m_pSearchService = Eegeo_NEW(Yelp::SdkModel::YelpSearchService)(*m_pSearchQueryFactory,
                                                                                *m_pYelpBusinessQueryFactory,
                                                                                *m_pYelpSearchJsonParser,
                                                                                networkCapabilities,
                                                                                Yelp::SearchConstants::GetCategories());
            }

            YelpSearchServiceModule::~YelpSearchServiceModule()
            {
                Eegeo_DELETE m_pSearchService;
                Eegeo_DELETE m_pSearchQueryFactory;
                Eegeo_DELETE m_pYelpBusinessQueryFactory;
                Eegeo_DELETE m_pYelpSearchJsonParser;
                Eegeo_DELETE m_pYelpBusinessJsonParser;
                Eegeo_DELETE m_pYelpCategoryMapper;
            }

            Search::SdkModel::ISearchService& YelpSearchServiceModule::GetSearchService() const
            {
                return *m_pSearchService;
            }

            std::vector<CategorySearch::View::CategorySearchModel> YelpSearchServiceModule::GetCategorySearchModels() const
            {
                return Yelp::SearchConstants::GetCategorySearchModels();
            }
        }
    }
}