// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DecartaSearchConstants.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Decarta
        {
            namespace SearchConstants
            {
                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels()
                {
                    // Some DeCarta categories from http://developer.decarta.com/Docs/REST/Search#category
                    std::vector<ExampleApp::CategorySearch::View::CategorySearchModel> categories;
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Coffee", "coffee shop", "coffee"));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Food", "restaurant", "food"));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Nightlife", "night life", "nightlife"));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Arts", "museum", "arts"));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Hotels", "hotel", "hotel"));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Parks", "park", "park"));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Banks", "bank", "bank"));
                    return categories;
                }
                
                std::vector<std::string> GetCategories()
                {
                    std::vector<std::string> categories;
                    categories.push_back("coffee shop");
                    categories.push_back("restaurant");
                    categories.push_back("night life");
                    categories.push_back("museum");
                    categories.push_back("hotel");
                    categories.push_back("park");
                    categories.push_back("bank");
                    return categories;
                }
            }
        }
    }
}