// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SwallowSearchConstants.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SearchConstants
            {
                const std::string NAME_FIELD_NAME = "name";
                const std::string JOB_TITLE_FIELD_NAME = "job_title";
                const std::string IMAGE_FILENAME_FIELD_NAME = "image_filename";
                const std::string WORKING_GROUP_FIELD_NAME = "working_group";
                const std::string OFFICE_LOCATION_FIELD_NAME = "office_location";
                const std::string DESK_CODE_FIELD_NAME = "desk_code";
                const std::string AVAILABILITY_FIELD_NAME = "availability";
                const std::string DESCRIPTION_FIELD_NAME = "description";
                const std::string DESKS_FIELD_NAME = "desks";
                const std::string CATEGORY_FIELD_NAME = "category";
                const std::string SUBCATEGORY_FIELD_NAME = "subcategory";
                const std::string DISTANCE_FIELD_NAME = "distance";
                const std::string HEADING_DEGREES_FIELD_NAME = "heading_degrees";
                const std::string TARGET_INTERIOR_ID_FIELD_NAME = "target_interior_id";
                const std::string TARGET_INTERIOR_FLOOR_FIELD_NAME = "target_interior_floor";
                const std::string TARGET_LATITUDE_DEGREES_FIELD_NAME = "target_latitude_degrees";
                const std::string TARGET_LONGITUDE_DEGREES_FILED_NAME = "target_longitude_degrees";
                
                const std::string PERSON_CATEGORY_NAME = "person";
                const std::string MEETING_ROOM_CATEGORY_NAME = "meeting_room";
                const std::string WORKING_GROUP_CATEGORY_NAME = "working_group";
                const std::string FACILITY_CATEGORY_NAME = "facility";
                const std::string OFFICE_CATEGORY_NAME = "office";
                const std::string DEPARTMENT_CATEGORY_NAME = "department";
                const std::string TRANSITION_CATEGORY_NAME = "transition";
                const std::string STATIONERY_CATEGORY_NAME = "stationery";
                const std::string TOILETS_CATEGORY_NAME = "toilets";
                const std::string PRINT_STATION_CATEGORY_NAME = "print_station";
                const std::string EMERGENCY_EXIT_CATEGORY_NAME = "emergency_exit";
                
                const std::string MEETING_ROOM_AVAILABLE = "available";
                const std::string MEETING_ROOM_AVAILABLE_SOON = "available_soon";
                const std::string MEETING_ROOM_OCCUPIED = "occupied";
                
                const std::string MEETING_ROOM_CATEGORY_AVAILABLE = "meeting_room_avail";
                const std::string MEETING_ROOM_CATEGORY_AVAILABLE_SOON = "meeting_room_avail_soon";
                const std::string MEETING_ROOM_CATEGORY_OCCUPIED = "meeting_room_occupied";
                
                const int MEETING_ROOM_AVAILABLE_PRIORITY = 0;
                const int MEETING_ROOM_AVAILABLE_SOON_PRIORITY = 1;
                const int MEETING_ROOM_OCCUPIED_PRIORITY = 2;
                const int MEETING_ROOM_MAX_PRIORITY = 3;
                
                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels()
                {
                    const bool showCategoriesInSearchMenu = false;
                    
                    std::vector<ExampleApp::CategorySearch::View::CategorySearchModel> categories;
                    
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Meeting Rooms", MEETING_ROOM_CATEGORY_NAME, true, "meetingroom", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Working Groups", WORKING_GROUP_CATEGORY_NAME, false, "workinggroup", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Facilities", FACILITY_CATEGORY_NAME, true, "toilets", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Buildings", OFFICE_CATEGORY_NAME, false, "office", showCategoriesInSearchMenu));
                    
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Toilets", OFFICE_CATEGORY_NAME, true, "toilets", false));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Print Stations", PRINT_STATION_CATEGORY_NAME, true, "printstation", false));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Stationary", STATIONERY_CATEGORY_NAME, true, "stationary", false));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("People", PERSON_CATEGORY_NAME, false, "person", false));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Department", DEPARTMENT_CATEGORY_NAME, false, "department", false));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Transitions", TRANSITION_CATEGORY_NAME, false, "transition", false));
                    return categories;
                }
                
                std::vector<std::string> GetAllCategories()
                {
                    std::vector<std::string> categories;
                    
                    categories.push_back(MEETING_ROOM_CATEGORY_NAME);
                    categories.push_back(WORKING_GROUP_CATEGORY_NAME);
                    categories.push_back(FACILITY_CATEGORY_NAME);
                    categories.push_back(OFFICE_CATEGORY_NAME);
                    categories.push_back(TOILETS_CATEGORY_NAME);
                    categories.push_back(PRINT_STATION_CATEGORY_NAME);
                    categories.push_back(DEPARTMENT_CATEGORY_NAME);
                    categories.push_back(STATIONERY_CATEGORY_NAME);
                    categories.push_back(PERSON_CATEGORY_NAME);
                    categories.push_back(TRANSITION_CATEGORY_NAME);
                    
                    return categories;
                }
                
                std::vector<std::string> GetCategories()
                {
                    std::vector<std::string> categories;
                    
                    categories.push_back(MEETING_ROOM_CATEGORY_NAME);
                    categories.push_back(WORKING_GROUP_CATEGORY_NAME);
                    categories.push_back(FACILITY_CATEGORY_NAME);
                    categories.push_back(OFFICE_CATEGORY_NAME);
                    
                    return categories;
                }
                
                bool ShouldShowCategoryAsSearchResult(const std::string& category)
                {
                    if(category == TRANSITION_CATEGORY_NAME)
                    {
                        return false;
                    }
                    
                    return true;
                }
            }
        }
    }
}