// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "YelpSearchConstants.h"

//
// Yelp categories from http://www.yelp.com/developers/documentation/v2/all_category_list
//

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SearchConstants
            {
                std::string GetDefaultCategory() { return "misc"; }
                
                std::map<std::string, std::string> GetYelpFoundationCategoryToApplicationCategoryMap()
                {
                    std::map<std::string, std::string> yelpToApplicationCategoryMap;
                    
                    yelpToApplicationCategoryMap["food"] = "coffee";
                    yelpToApplicationCategoryMap["restaurants"] = "restaurants";
                    yelpToApplicationCategoryMap["nightlife"] = "nightlife";
                    yelpToApplicationCategoryMap["arts"] = "museums";
                    yelpToApplicationCategoryMap["galleries"] = "museums";
                    yelpToApplicationCategoryMap["eventservices"] = "museums";
                    yelpToApplicationCategoryMap["venues"] = "museums";
                    yelpToApplicationCategoryMap["hotelstravel"] = "hotels";
                    yelpToApplicationCategoryMap["active"] = "parks";
                    yelpToApplicationCategoryMap["financialservices"] = "financialservices";
                    
                    return yelpToApplicationCategoryMap;
                }
                
                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels()
                {
                    const bool showCategoriesInSearchMenu = true;
                    
                    std::vector<ExampleApp::CategorySearch::View::CategorySearchModel> categories;
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Around Me", "", false, "aroundme", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Coffee", "coffee", false, "coffee", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Food", "restaurants", false, "restaurants", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Nightlife", "nightlife", false, "nightlife", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Arts", "museums", false, "museums", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Hotels", "hotels", false, "hotels", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Parks", "parks", false, "parks", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Banks", "financialservices", false, "financialservices", showCategoriesInSearchMenu));
					
                    return categories;
                }
                
                std::vector<std::string> GetCategories()
                {
                    std::vector<std::string> categories;
                    categories.push_back("");
                    categories.push_back("coffee");
                    categories.push_back("restaurants");
                    categories.push_back("nightlife");
                    categories.push_back("museums");
                    categories.push_back("hotels");
                    categories.push_back("parks");
                    categories.push_back("financialservices");
                    categories.push_back("active");
                    return categories;
                }
            }
        }
    }
}
