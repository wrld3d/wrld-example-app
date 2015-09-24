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
                class IYelpCategoryMapper
                {
                public:
                    virtual ~IYelpCategoryMapper() { }
                    
                    virtual bool TryGetBestMatchingApplicationCategoryForYelpCategories(const std::vector<std::string>& yelpCategories,
                                                                                        std::string& out_bestMatchedAppCategory) = 0;
                };
            }
        }
    }
}
