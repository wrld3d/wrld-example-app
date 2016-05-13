// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "LaxSearchConstants.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
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
                
                
                const std::string DEFIBRILLATOR_CATEGORY_NAME = "defibrillator";
                const std::string FOOD_CATEGORY_NAME = "food";
                const std::string SHOPPING_CATEGORY_NAME = "shopping";
                const std::string ELEVATOR_CATEGORY_NAME = "elevator";
                const std::string STAIRS_CATEGORY_NAME = "stairs";
                const std::string ESCALATOR_CATEGORY_NAME = "escalator";
                const std::string RESTROOM_CATEGORY_NAME = "restroom";
                const std::string TDD_PAYPHONE_CATEGORY_NAME = "tdd_pay_phone";
                const std::string ATM_CATEGORY_NAME = "atm";
                const std::string PAYPHONE_CATEGORY_NAME = "pay_phone";
                const std::string GATES_CATEGORY_NAME = "gates";
                const std::string OTHERS_CATEGORY_NAME = "others";
                
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
                
//                const int MEETING_ROOM_AVAILABLE_PRIORITY = 0;
//                const int MEETING_ROOM_AVAILABLE_SOON_PRIORITY = 1;
//                const int MEETING_ROOM_OCCUPIED_PRIORITY = 2;
//                const int MEETING_ROOM_MAX_PRIORITY = 3;
//                
                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels()
                {
                    const bool showCategoriesInSearchMenu = false;
                    
                    std::vector<ExampleApp::CategorySearch::View::CategorySearchModel> categories;
                    
//                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Meeting Rooms", MEETING_ROOM_CATEGORY_NAME, true, "meetingroom", showCategoriesInSearchMenu));
                    
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Defribilator", DEFIBRILLATOR_CATEGORY_NAME, true, "defibrillator", showCategoriesInSearchMenu));

                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Food", FOOD_CATEGORY_NAME, true, "food", showCategoriesInSearchMenu));

                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Shopping", SHOPPING_CATEGORY_NAME, true, "shopping", showCategoriesInSearchMenu));

                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Elevator", ELEVATOR_CATEGORY_NAME, true, "elevator", showCategoriesInSearchMenu));

                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Stairs", STAIRS_CATEGORY_NAME, true, "stairs", showCategoriesInSearchMenu));

                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Escalator", ESCALATOR_CATEGORY_NAME, true, "escalator", showCategoriesInSearchMenu));

                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Restroom", RESTROOM_CATEGORY_NAME, true, "restroom", showCategoriesInSearchMenu));
                    
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Tddpayphone", TDD_PAYPHONE_CATEGORY_NAME, true, "tddpayphone", showCategoriesInSearchMenu));

                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Atm", ATM_CATEGORY_NAME, true, "atm", showCategoriesInSearchMenu));

                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Payphone", PAYPHONE_CATEGORY_NAME, true, "payphone", showCategoriesInSearchMenu));
                    
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Gates", GATES_CATEGORY_NAME, true, "gates", showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Others", OTHERS_CATEGORY_NAME, true, "others", showCategoriesInSearchMenu));
                    
//                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Working Groups", WORKING_GROUP_CATEGORY_NAME, false, "workinggroup", showCategoriesInSearchMenu));
//                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Facilities", FACILITY_CATEGORY_NAME, true, "toilets", showCategoriesInSearchMenu));
//                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Offices", OFFICE_CATEGORY_NAME, false, "office", showCategoriesInSearchMenu));
//                    
//                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Toilets", OFFICE_CATEGORY_NAME, true, "toilets", false));
//                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Print Stations", PRINT_STATION_CATEGORY_NAME, true, "printstation", false));
//                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Stationary", STATIONERY_CATEGORY_NAME, true, "stationary", false));
//                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("People", PERSON_CATEGORY_NAME, false, "person", false));
//                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Department", DEPARTMENT_CATEGORY_NAME, false, "department", false));
//                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Transitions", TRANSITION_CATEGORY_NAME, false, "transition", false));
                    return categories;
                }
                
                std::vector<std::string> GetAllCategories()
                {
                    std::vector<std::string> categories;
                    
                    categories.push_back(MEETING_ROOM_CATEGORY_NAME);
                    categories.push_back(DEFIBRILLATOR_CATEGORY_NAME);
                    
                    categories.push_back(FOOD_CATEGORY_NAME);
                    categories.push_back(SHOPPING_CATEGORY_NAME);
                    categories.push_back(ELEVATOR_CATEGORY_NAME);
                    categories.push_back(STAIRS_CATEGORY_NAME);

                    categories.push_back(ESCALATOR_CATEGORY_NAME);
                    categories.push_back(RESTROOM_CATEGORY_NAME);
                    categories.push_back(TDD_PAYPHONE_CATEGORY_NAME);
                    categories.push_back(ATM_CATEGORY_NAME);
                    categories.push_back(PAYPHONE_CATEGORY_NAME);
                    categories.push_back(GATES_CATEGORY_NAME);
                    categories.push_back(OTHERS_CATEGORY_NAME);
                    
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
                    categories.push_back(DEFIBRILLATOR_CATEGORY_NAME);
                    
                    categories.push_back(FOOD_CATEGORY_NAME);
                    categories.push_back(SHOPPING_CATEGORY_NAME);
                    categories.push_back(ELEVATOR_CATEGORY_NAME);
                    categories.push_back(STAIRS_CATEGORY_NAME);
                    categories.push_back(ESCALATOR_CATEGORY_NAME);
                    categories.push_back(RESTROOM_CATEGORY_NAME);
                    categories.push_back(TDD_PAYPHONE_CATEGORY_NAME);                    
                    categories.push_back(ATM_CATEGORY_NAME);
                    categories.push_back(PAYPHONE_CATEGORY_NAME);
                    categories.push_back(GATES_CATEGORY_NAME);
                    categories.push_back(OTHERS_CATEGORY_NAME);
                    
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