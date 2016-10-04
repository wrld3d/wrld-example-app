// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Yelp.h"
#include "Search.h"
#include "TagSearch.h"
#include <string>

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                class YelpBusinessJsonParser : private Eegeo::NonCopyable
                {
                public:
                    YelpBusinessJsonParser(IYelpCategoryToTagMapper& yelpCategoryMapper,
                                           const TagSearch::SdkModel::ITagIconMapper& tagIconMapper);
                    
                    bool TryParse(const std::string& responseString, Search::SdkModel::SearchResultModel& out_result) const;
                    
                private:
                    IYelpCategoryToTagMapper& m_yelpCategoryMapper;
                    const TagSearch::SdkModel::ITagIconMapper& m_tagIconMapper;
                };
            }
        }
    }
}