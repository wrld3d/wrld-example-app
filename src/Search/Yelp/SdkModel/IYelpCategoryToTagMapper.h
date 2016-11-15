// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                class IYelpCategoryToTagMapper
                {
                public:
                    virtual ~IYelpCategoryToTagMapper() { }
                    
                    virtual bool TryGetBestMatchingTagForYelpCategories(const std::vector<std::string>& yelpCategories,
                            std::string& out_bestMatchedAppTag) = 0;
                };
            }
        }
    }
}
