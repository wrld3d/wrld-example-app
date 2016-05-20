// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "IconResources.h"
#include "ImageHelpers.h"

namespace
{
    bool Contains(const std::string& string, const std::string& searchFor)
    {
        return string.find(searchFor) != std::string::npos;
    }
}

namespace ExampleApp
{
    namespace Helpers
    {
        namespace IconResources
        {
            std::string GetCategoryMatch(std::string category)
            {
                std::transform(category.begin(), category.end(), category.begin(), ::tolower);
                
                if(Contains(category, "around me"))
                {
                    return "icon1_aroundme";
                }
                if(Contains(category, "caf\xc3\xa9") || Contains(category, "cafe") || Contains(category, "coffee"))
                {
                    return "icon1_coffee";
                }
                if(Contains(category, "nightlife") || Contains(category, "night life"))
                {
                    return "icon1_nightlife";
                }
                if(Contains(category, "museums") || Contains(category, "museum") || category == "arts")
                {
                    return "icon1_museums";
                }
                if(Contains(category, "park"))
                {
                    return "icon1_parks";
                }
                if(Contains(category, "bank") || Contains(category, "financialservices"))
                {
                    return "icon1_financialservices";
                }
                if(Contains(category, "hotel"))
                {
                    return "icon1_hotels";
                }
                if(Contains(category, "restaurant") || Contains(category, "food"))
                {
                    return "icon1_restaurants";
                }
                if(Contains(category, "tours"))
                {
                    return "icon1_tours";
                }

                return "icon1_misc";
            }

            std::string GetSmallIconForCategory(const std::string& category)
            {
                return GetCategoryMatch(category);
            }

            std::string GetSmallIconPathForResourceName(const std::string& resource)
            {
                return "icon1_" + resource;
            }

            std::string GetSearchResultIconPathForResourceName(const std::string& resource)
            {
                return GetCategoryMatch(resource);
            }
        }
    }
}
