// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>
#include "CategorySearchModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SearchConstants
            {
                extern const std::string JOB_TITLE_FIELD_NAME;
                extern const std::string WORKING_GROUP_FIELD_NAME;
                extern const std::string OFFICE_LOCATION_FIELD_NAME;
                extern const std::string DESK_CODE_FIELD_NAME;
                
                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels();
                
                std::vector<std::string> GetCategories();
            }
        }
    }
}