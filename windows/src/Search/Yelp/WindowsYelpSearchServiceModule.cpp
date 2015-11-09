// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WindowsYelpSearchServiceModule.h"
#include "YelpSearchJsonParser.h"
#include "YelpSearchService.h"
#include "YelpCategoryMapper.h"
#include "YelpSearchConstants.h"
#include "ApiKey.h"
#include "WindowsYelpSearchQueryFactory.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            WindowsYelpSearchServiceModule::WindowsYelpSearchServiceModule(WindowsNativeState& nativeState,
                Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                Net::SdkModel::INetworkCapabilities& networkCapabilities,
                Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder)
            {
                m_pYelpCategoryMapper = Eegeo_NEW(Yelp::SdkModel::YelpCategoryMapper)(webRequestFactory,
                    Yelp::SearchConstants::GetYelpFoundationCategoryToApplicationCategoryMap(),
                    Yelp::SearchConstants::GetDefaultCategory());

                m_pSearchResultParser = Eegeo_NEW(Yelp::SdkModel::YelpSearchJsonParser)(*m_pYelpCategoryMapper);

                m_pSearchQueryFactory = Eegeo_NEW(Yelp::WindowsYelpSearchQueryFactory)(
                    nativeState,
                    ExampleApp::YelpConsumerKey,
                    ExampleApp::YelpConsumerSecret,
                    ExampleApp::YelpOAuthToken,
                    ExampleApp::YelpOAuthTokenSecret,
                    *m_pYelpCategoryMapper);

                m_pSearchService = Eegeo_NEW(Yelp::SdkModel::YelpSearchService)(*m_pSearchQueryFactory,
                    *m_pSearchResultParser,
                    networkCapabilities,
                    Yelp::SearchConstants::GetCategories());
            }

            WindowsYelpSearchServiceModule::~WindowsYelpSearchServiceModule()
            {
                Eegeo_DELETE m_pSearchService;
                Eegeo_DELETE m_pSearchQueryFactory;
                Eegeo_DELETE m_pSearchResultParser;
                Eegeo_DELETE m_pYelpCategoryMapper;
            }

            Search::SdkModel::ISearchService& WindowsYelpSearchServiceModule::GetSearchService() const
            {
                return *m_pSearchService;
            }

            std::vector<CategorySearch::View::CategorySearchModel> WindowsYelpSearchServiceModule::GetCategorySearchModels() const
            {
                return Yelp::SearchConstants::GetCategorySearchModels();
            }
        }
    }
}