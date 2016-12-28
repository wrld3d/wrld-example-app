// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <string>
namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                struct YelpCategoryModel
                {
                    std::string yelpCategoryFilter;
                    bool skipYelpSearch;
                };
            }
        }
    }
}