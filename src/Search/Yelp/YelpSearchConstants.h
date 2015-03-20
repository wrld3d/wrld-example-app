// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include <string>
#include <map>
#include "Search.h"
#include "CategorySearchModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            std::string GetDefaultCategory();
            
            std::map<std::string, std::string> GetYelpFoundationCategoryToApplicationCategoryMap();
            
            std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels();
        }
    }
}
