// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Search.h"
#include "Yelp.h"
#include "TagSearch.h"

#include <document.h>

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                namespace Helpers
                {
                    ExampleApp::Search::SdkModel::SearchResultModel ParseYelpSearchResultFromJsonObject(const rapidjson::Value& json,
                                                                                                        ExampleApp::Search::Yelp::SdkModel::IYelpCategoryToTagMapper& yelpCategoryMapper,
                                                                                                        const TagSearch::SdkModel::ITagIconMapper& tagIconMapper);
                    
                    YelpSearchResultModel TransformToYelpSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                    
                    bool TryParseImageDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_imageUrl);
                    
                    bool TryParseReviewDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_ratingImageUrl, int& out_reviewCount);
                    
                };
            }
        }
    }
}