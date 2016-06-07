// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "YelpSearchConstants.h"
#include "Document.h"

//
// Yelp categories from http://www.yelp.com/developers/documentumentation/v2/all_category_list
//

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SearchConstants
            {
                namespace
                {
                    std::string GetFileContents(Eegeo::Helpers::IFileIO& fileIO, const std::string& fileName)
                    {
                        std::string contents;

                        std::fstream file;
                        std::size_t size;

                        if (fileIO.OpenFile(file, size, fileName, std::ios::in))
                        {
                            contents = std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
                        }

                        return contents;
                    }
                }
                
                std::string GetDefaultCategory() { return "misc"; }

                std::map<std::string, std::string> GetYelpFoundationCategoryToApplicationCategoryMap(Eegeo::Helpers::IFileIO& fileIO)
                {
                    std::map<std::string, std::string> yelpToApplicationCategoryMap;

                    std::string contents = GetFileContents(fileIO, "yelp_map.json");

                    rapidjson::Document document;

                    if (document.Parse<0>(contents.c_str()).HasParseError())
                    {
                        Eegeo_TTY("Warning: Cannot parse Yelp Category Map!!");
                        return yelpToApplicationCategoryMap;
                    }

                    std::vector<std::string> categories = GetCategories();

                    for (std::vector<std::string>::const_iterator it = categories.begin();
                        it != categories.end();
                        ++it)
                    {
                        const std::string& category = (*it);

                        if (!document.HasMember(category.c_str()))
                        {
                            continue;
                        }
                        
                        rapidjson::GenericValue<rapidjson::UTF8<> >& list = document[category.c_str()];

                        if (!list.IsArray())
                        {
                            continue;
                        }
                        
                        for (rapidjson::Value::ValueIterator iter = list.Begin();
                            iter != list.End();
                            ++iter)
                        {
                            yelpToApplicationCategoryMap.insert(std::make_pair(iter->GetString(), category));
                        }
                    }
                    
                    return yelpToApplicationCategoryMap;
                }
                
                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels()
                {
                    const bool showCategoriesInSearchMenu = true;
                    
                    std::vector<ExampleApp::CategorySearch::View::CategorySearchModel> categories;
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Around Me", "", false, "aroundme", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Accommodation", "accommodation", false, "accommodation", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Art & Museum", "art_museums", false, "art_museums", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Business", "business", false, "business", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Entertainment", "entertainment", false, "entertainment", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Food & Drink", "food_drink", false, "food_drink", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("General Amenities", "amenities", false, "amenities", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Health", "health", false, "health", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Shopping", "shopping", false, "shopping", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Sport & Leisure", "sports_leisure", false, "sports_leisure", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Tourist", "tourism", false, "tourism", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Transport", "transport", false, "transport", showCategoriesInSearchMenu));

                    return categories;
                }
                
                std::vector<std::string> GetCategories()
                {
                    std::vector<std::string> categories;
                    categories.push_back("");
                    categories.push_back("accommodation");
                    categories.push_back("art_museums");
                    categories.push_back("business");
                    categories.push_back("entertainment");
                    categories.push_back("food_drink");
                    categories.push_back("amenities");
                    categories.push_back("health");
                    categories.push_back("shopping");
                    categories.push_back("sports_leisure");
                    categories.push_back("tourism");
                    categories.push_back("transport");
                    return categories;
                }

                std::map<std::string, std::string> GetApplicationToYelpCategoryMap()
                {
                    std::map<std::string, std::string> applicationMap;

                    applicationMap["accommodation"] = "hotels";
                    applicationMap["art_museums"] = "museums";
                    applicationMap["business"] = "professional";
                    applicationMap["entertainment"] = "arts";
                    applicationMap["food_drink"] = "food";
                    applicationMap["amenities"] = "homeservices";
                    applicationMap["health"] = "health";
                    applicationMap["shopping"] = "shopping";
                    applicationMap["sports_leisure"] = "active";
                    applicationMap["tourism"] = "tours";
                    applicationMap["transport"] = "transport";

                    return applicationMap;
                }
            }
        }
    }
}
