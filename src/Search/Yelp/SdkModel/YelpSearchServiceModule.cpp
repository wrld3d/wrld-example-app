// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "YelpSearchServiceModule.h"
#include "YelpSearchJsonParser.h"
#include "YelpSearchService.h"
#include "YelpCategoryMapper.h"
#include "YelpSearchConstants.h"
#include "ApiKey.h"
#include "YelpSearchQueryFactory.h"

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
				const std::string& yelpOAuthTokenSecret)
            {
                m_pYelpCategoryMapper = Eegeo_NEW(Yelp::SdkModel::YelpCategoryMapper)(webRequestFactory,
                    Yelp::SearchConstants::GetYelpFoundationCategoryToApplicationCategoryMap(),
                    Yelp::SearchConstants::GetDefaultCategory());

                m_pSearchResultParser = Eegeo_NEW(Yelp::SdkModel::YelpSearchJsonParser)(*m_pYelpCategoryMapper);

                m_pSearchQueryFactory = Eegeo_NEW(Yelp::SdkModel::YelpSearchQueryFactory)(
                    yelpConsumerKey,
                    yelpConsumerSecret,
                    yelpOAuthToken,
                    yelpOAuthTokenSecret,
                    *m_pYelpCategoryMapper,
                    webRequestFactory);

                m_pSearchService = Eegeo_NEW(Yelp::SdkModel::YelpSearchService)(*m_pSearchQueryFactory,
                    *m_pSearchResultParser,
                    networkCapabilities,
                    Yelp::SearchConstants::GetCategories());
            }

            YelpSearchServiceModule::~YelpSearchServiceModule()
            {
                Eegeo_DELETE m_pSearchService;
                Eegeo_DELETE m_pSearchQueryFactory;
                Eegeo_DELETE m_pSearchResultParser;
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