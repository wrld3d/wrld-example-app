// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Search.h"
#include "Yelp.h"
#include "ISearchResultParser.h"
#include "Types.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                class YelpSearchJsonParser : public Search::SdkModel::ISearchResultParser, private Eegeo::NonCopyable
                {
                    IYelpCategoryMapper& m_yelpCategoryMapper;
                    
                public:
                    YelpSearchJsonParser(IYelpCategoryMapper& yelpCategoryMapper);
                    
                    void ParseSearchResults(const std::string& serialized,
                                            std::vector<Search::SdkModel::SearchResultModel>& out_results);
                };
                
                bool TryParseYelpBusinessSearchResult(const std::string& serialized,
                                                      IYelpCategoryMapper& yelpCategoryMapper,
                                                      Search::SdkModel::SearchResultModel& out_result);
                
                YelpSearchResultModel TransformToYelpSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel);

                bool TryParseImageDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_imageUrl, std::string& out_ratingImageUrl);

                bool TryParseReviewDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_ratingImageUrl, int& out_reviewCount);
            }
        }
    }
}

