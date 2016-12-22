// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "YelpCategoryModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                class ISearchTagToYelpCategoryMapper
                {
                public:
                    virtual ~ISearchTagToYelpCategoryMapper() { }
                    
                    virtual bool TryGetBestYelpCategoryForSearchTag(const std::string& searchTag, YelpCategoryModel& out_bestMatchingYelpCategory) = 0;
                    virtual void AddMapping(const std::string& tag, const YelpCategoryModel& yelpCategoryModel) = 0;
                    virtual void RemoveMapping(const std::string& tag) = 0;
                    virtual void OnYelpCategoryMapperAdded(const std::string& tag, const YelpCategoryModel& yelpCategoryModel) = 0;
                };
            }
        }
    }
}
