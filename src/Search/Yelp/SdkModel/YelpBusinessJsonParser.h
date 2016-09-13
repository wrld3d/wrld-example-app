// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "Yelp.h"
#include "Search.h"

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
                    YelpBusinessJsonParser(const std::shared_ptr<IYelpCategoryToTagMapper>& yelpCategoryMapper);
                    
                    bool TryParse(const std::string& responseString, Search::SdkModel::SearchResultModel& out_result) const;
                    
                private:
                    std::shared_ptr<IYelpCategoryToTagMapper> m_yelpCategoryMapper;
                };
            }
        }
    }
}