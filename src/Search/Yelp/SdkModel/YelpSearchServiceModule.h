// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Yelp.h"
#include "Search.h"
#include "Web.h"
#include "NetIncludes.h"
#include "UrlHelpers.h"
#include "ISearchServiceModule.h"
#include "IFileIO.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            class YelpSearchServiceModule : public Search::SdkModel::ISearchServiceModule, private Eegeo::NonCopyable
            {
                Search::SdkModel::ISearchService* m_pSearchService;
                Yelp::SdkModel::YelpSearchQueryFactory* m_pSearchQueryFactory;
                Yelp::SdkModel::YelpBusinessQueryFactory* m_pYelpBusinessQueryFactory;
                Search::SdkModel::ISearchResultParser* m_pYelpSearchJsonParser;
                Yelp::SdkModel::YelpBusinessJsonParser* m_pYelpBusinessJsonParser;
                Yelp::SdkModel::IYelpCategoryMapper* m_pYelpCategoryMapper;

            public:
                YelpSearchServiceModule(
                    Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                    Net::SdkModel::INetworkCapabilities& networkCapabilities,
                    Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
					const std::string& yelpConsumerKey,
					const std::string& yelpConsumerSecret,
					const std::string& yelpOAuthToken,
					const std::string& yelpOAuthTokenSecret,
                    Eegeo::Helpers::IFileIO& fileIO);

                ~YelpSearchServiceModule();

                Search::SdkModel::ISearchService& GetSearchService() const;

                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels() const;
            };
        }
    }
}