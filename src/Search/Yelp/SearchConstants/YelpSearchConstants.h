// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include <string>
#include <map>
#include "Search.h"
#include "TagSearchModel.h"
#include "IFileIO.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SearchConstants
            {
                struct YelpCategoryMappingData
                {
                    std::map<std::string, std::string> yelpFoundationCategoryToAppTag;
                    std::map<std::string, std::string> appTagToYelpCategory;
                    std::string defaultAppTag;
                };

                YelpCategoryMappingData ParseYelpData(
                        Eegeo::Helpers::IFileIO& fileIO,
                        const std::vector<std::string>& appTags,
                        const std::string& fileName);
            }
        }
    }
}
