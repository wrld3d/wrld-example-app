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
        namespace Decarta
        {
            namespace SearchConstants
            {
                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels();
            
                std::vector<std::string> GetCategories();
            }
        }
    }
}
