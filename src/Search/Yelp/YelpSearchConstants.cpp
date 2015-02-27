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
            std::string GetDefaultCategory() { return "misc"; }
            
            std::map<std::string, std::string> GetYelpFoundationCategoryToApplicationCategoryMap()
            {
                std::map<std::string, std::string> yelpToApplicationCategoryMap;
                
                yelpToApplicationCategoryMap["food"] = "coffee";
                yelpToApplicationCategoryMap["restaurants"] = "food";
                yelpToApplicationCategoryMap["nightlife"] = "nightlife";
                yelpToApplicationCategoryMap["arts"] = "arts";
                yelpToApplicationCategoryMap["galleries"] = "arts";
                yelpToApplicationCategoryMap["eventservices"] = "arts";
                yelpToApplicationCategoryMap["venues"] = "arts";
                yelpToApplicationCategoryMap["hotelstravel"] = "hotel";
                yelpToApplicationCategoryMap["active"] = "park";
                yelpToApplicationCategoryMap["financialservices"] = "bank";
                
                return yelpToApplicationCategoryMap;
            }
            
            std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels()
            {
                std::vector<ExampleApp::CategorySearch::View::CategorySearchModel> categories;
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Around Me", "", "aroundme"));
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Coffee", "coffee", "coffee"));
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Food", "restaurants", "food"));
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Nightlife", "nightlife", "nightlife"));
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Arts", "museums", "arts"));
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Hotels", "hotels", "hotel"));
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Parks", "parks", "park"));
                categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Banks", "financialservices", "bank"));
                return categories;
            }
        }
    }
}
