// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include <string>
#include <map>
#include "Search.h"
#include "CategorySearchModel.h"
#include "IFileIO.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SearchConstants
            {
                std::string GetDefaultCategory();
                
                std::map<std::string, std::string> GetYelpFoundationCategoryToApplicationCategoryMap(Eegeo::Helpers::IFileIO& fileIO);
                
                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels();
                
                std::vector<std::string> GetCategories();

                std::map<std::string, std::string> GetApplicationToYelpCategoryMap();
            }
        }
    }
}
