// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "IconResources.h"
#include "ImageHelpers.h"

#include "SwallowSearchConstants.h"

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
                if(Contains(category, "museum") || category == "arts")
                {
                    return "icon1_arts";
                }
                if(Contains(category, "park"))
                {
                    return "icon1_park";
                }
                if(Contains(category, "bank"))
                {
                    return "icon1_bank";
                }
                if(Contains(category, "hotel"))
                {
                    return "icon1_hotel";
                }
                if(Contains(category, "restaurant") || Contains(category, "food"))
                {
                    return "icon1_food";
                }
                if(Contains(category, Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME))
                {
                    return "icon1_person";
                }
                if(Contains(category, Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME) || Contains(category, "meeting"))
                {
                    return "icon1_meeting_room";
                }
                if(Contains(category, Search::Swallow::SearchConstants::DEPARTMENT_CATEGORY_NAME))
                {
                    return "icon1_department";
                }
                if(Contains(category, Search::Swallow::SearchConstants::WORKING_GROUP_CATEGORY_NAME) || Contains(category, "working"))
                {
                    return "icon1_working_group";
                }
                if(Contains(category, Search::Swallow::SearchConstants::OFFICE_CATEGORY_NAME))
                {
                    return "icon1_office";
                }
                if(Contains(category, Search::Swallow::SearchConstants::STATIONERY_CATEGORY_NAME))
                {
                    return "icon1_stationery";
                }
                if(Contains(category, Search::Swallow::SearchConstants::TOILETS_CATEGORY_NAME))
                {
                    return "icon1_toilets";
                }
                if(Contains(category, Search::Swallow::SearchConstants::PRINT_STATION_CATEGORY_NAME))
                {
                    return "icon1_printer";
                }
                if(Contains(category, Search::Swallow::SearchConstants::EMERGENCY_EXIT_CATEGORY_NAME))
                {
                    return "icon1_emergencyexit";
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
