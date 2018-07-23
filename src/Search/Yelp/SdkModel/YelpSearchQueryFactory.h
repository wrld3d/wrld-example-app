// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Search.h"
#include "ICallback.h"
#include "IdentitySearchCallbackData.h"
#include "SearchResultModel.h"
#include "Yelp.h"
#include "IWebLoadRequestFactory.h"
#include "SearchTagToYelpCategoryMapper.h"
#include "AppCamera.h"


namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                class YelpSearchQueryFactory
                {
                public:
                    YelpSearchQueryFactory(
                        const std::string& yelpApiKey,
                        SdkModel::SearchTagToYelpCategoryMapper& searchTagToYelpCategoryMap,
                        Eegeo::Web::IWebLoadRequestFactory& webRequestFactory,
                        ExampleApp::AppCamera::SdkModel::IAppCameraController& cameraController);
                    
                    ~YelpSearchQueryFactory();
                    
                    IYelpSearchQuery* CreateYelpSearchForQuery(const Search::SdkModel::SearchQuery& query,
                                                               Eegeo::Helpers::ICallback0& completionCallback);
                    
                private:
                    const std::string m_apiUrl;
                    const std::string m_yelpApiKey;
                    
                    Eegeo::Web::IWebLoadRequestFactory& m_webRequestFactory;
                    SdkModel::SearchTagToYelpCategoryMapper& m_searchTagToYelpCategoryMap;
                    ExampleApp::AppCamera::SdkModel::IAppCameraController& m_cameraController;
                };
            }
        }
    }
}
