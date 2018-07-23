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
#include "TagSearch.h"
#include "SearchTags.h"
#include "YelpCategoryMapperUpdater.h"
#include "SearchTagToYelpCategoryMapper.h"
#include "AppCamera.h"

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
                Yelp::SdkModel::IYelpCategoryToTagMapper* m_pYelpCategoryMapper;
                TagSearch::SdkModel::ITagIconMapper *m_pTagIconMapper;
                Yelp::SdkModel::SearchTagToYelpCategoryMapper *m_pSearchTagToYelpCategoryMapper;

            public:
                YelpSearchServiceModule(
                    Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                    Net::SdkModel::INetworkCapabilities& networkCapabilities,
                    Eegeo::Helpers::UrlHelpers::IUrlEncoder& urlEncoder,
                    const Search::SdkModel::SearchTags& searchTags,
                    const std::string& yelpApiKey,
                    Eegeo::Helpers::IFileIO& fileIO,
                    Search::Yelp::SdkModel::YelpCategoryMapperUpdater& yelpCategoryMapperUpdater,
                    ExampleApp::AppCamera::SdkModel::IAppCameraController& cameraController);

                ~YelpSearchServiceModule();

                Search::SdkModel::ISearchService& GetSearchService() const;
                Yelp::SdkModel::IYelpCategoryToTagMapper& GetYelpCategoryMapper() const;
            };
        }
    }
}
