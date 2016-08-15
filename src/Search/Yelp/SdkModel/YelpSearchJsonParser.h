// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "Search.h"
#include "Yelp.h"
#include "ISearchResultParser.h"
#include "Types.h"

#include <document.h>

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
            }
        }
    }
}

