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
                const std::string RECEPTION_CATEGORY_NAME = "reception";
                const std::string TOILETS_CATEGORY_NAME = "toilets";
                const std::string PRINT_STATION_CATEGORY_NAME = "printer";
                const std::string EMERGENCY_EXIT_CATEGORY_NAME = "emergency_exit";
                
                const std::string MEETING_ROOM_AVAILABLE = "available";
                const std::string MEETING_ROOM_AVAILABLE_SOON = "available_soon";
                const std::string MEETING_ROOM_OCCUPIED = "occupied";

                const int MEETING_ROOM_AVAILABLE_STATE = 1;
                const int MEETING_ROOM_AVAILABLE_SOON_STATE = 2;
                const int MEETING_ROOM_OCCUPIED_STATE = 3;
                
                const std::string MEETING_ROOM_ICON_AVAILABLE = "meeting_room_available";
                const std::string MEETING_ROOM_ICON_AVAILABLE_SOON = "meeting_room_available_soon";
                const std::string MEETING_ROOM_ICON_OCCUPIED = "meeting_room_unavailable";
                
                std::vector<TagSearch::View::TagSearchModel> GetTagSearchModels()
                {
                    const bool showCategoriesInSearchMenu = false;
                    
                    std::vector<ExampleApp::TagSearch::View::TagSearchModel> tags;
                    
                    tags.push_back(ExampleApp::TagSearch::View::TagSearchModel("Meeting Rooms", MEETING_ROOM_CATEGORY_NAME, true, "meetingroom", showCategoriesInSearchMenu));
                    tags.push_back(ExampleApp::TagSearch::View::TagSearchModel("Working Groups", WORKING_GROUP_CATEGORY_NAME, false, "workinggroup", showCategoriesInSearchMenu));
                    tags.push_back(ExampleApp::TagSearch::View::TagSearchModel("Facilities", FACILITY_CATEGORY_NAME, true, "toilets", showCategoriesInSearchMenu));
                    tags.push_back(ExampleApp::TagSearch::View::TagSearchModel("Buildings", OFFICE_CATEGORY_NAME, false, "office", showCategoriesInSearchMenu));
                    
                    tags.push_back(ExampleApp::TagSearch::View::TagSearchModel("Toilets", OFFICE_CATEGORY_NAME, true, "toilets", false));
                    tags.push_back(ExampleApp::TagSearch::View::TagSearchModel("Print Stations", PRINT_STATION_CATEGORY_NAME, true, "printstation", false));
                    tags.push_back(ExampleApp::TagSearch::View::TagSearchModel("Stationary", STATIONERY_CATEGORY_NAME, true, "stationary", false));
                    tags.push_back(ExampleApp::TagSearch::View::TagSearchModel("People", PERSON_CATEGORY_NAME, false, "person", false));
                    tags.push_back(ExampleApp::TagSearch::View::TagSearchModel("Department", DEPARTMENT_CATEGORY_NAME, false, "department", false));
                    tags.push_back(ExampleApp::TagSearch::View::TagSearchModel("Transitions", TRANSITION_CATEGORY_NAME, false, "transition", false));
                    return tags;
                }
                
                std::vector<std::string> GetAllTags()
                {
                    std::vector<std::string> tags;
                    
                    tags.push_back(MEETING_ROOM_CATEGORY_NAME);
                    tags.push_back(WORKING_GROUP_CATEGORY_NAME);
                    tags.push_back(FACILITY_CATEGORY_NAME);
                    tags.push_back(OFFICE_CATEGORY_NAME);
                    tags.push_back(TOILETS_CATEGORY_NAME);
                    tags.push_back(PRINT_STATION_CATEGORY_NAME);
                    tags.push_back(DEPARTMENT_CATEGORY_NAME);
                    tags.push_back(STATIONERY_CATEGORY_NAME);
                    tags.push_back(RECEPTION_CATEGORY_NAME);
                    tags.push_back(PERSON_CATEGORY_NAME);
                    tags.push_back(TRANSITION_CATEGORY_NAME);
                    
                    return tags;
                }
                
                std::vector<std::string> GetTags()
                {
                    std::vector<std::string> tags;
                    
                    tags.push_back(MEETING_ROOM_CATEGORY_NAME);
                    tags.push_back(WORKING_GROUP_CATEGORY_NAME);
                    tags.push_back(FACILITY_CATEGORY_NAME);
                    tags.push_back(OFFICE_CATEGORY_NAME);
                    
                    return tags;
                }
                
                bool ShouldShowTagAsSearchResult(const std::string& tag)
                {
                    if(tag == TRANSITION_CATEGORY_NAME)
                    {
                        return false;
                    }
                    
                    return true;
                }

                std::string GetAvailabilityFromAvailabilityState(int availabilityState)
                {
                    if (availabilityState == MEETING_ROOM_AVAILABLE_STATE)
                    {
                        return MEETING_ROOM_AVAILABLE;
                    }
                    else if (availabilityState == MEETING_ROOM_AVAILABLE_SOON_STATE)
                    {
                        return MEETING_ROOM_AVAILABLE_SOON;
                    }
                    else if (availabilityState == MEETING_ROOM_OCCUPIED_STATE)
                    {
                        return MEETING_ROOM_OCCUPIED;
                    }

                    return MEETING_ROOM_AVAILABLE;
                }

                int GetAvailabilityStateFromAvailability(std::string availability)
                {
                    if (availability == MEETING_ROOM_AVAILABLE)
                    {
                        return MEETING_ROOM_AVAILABLE_STATE;
                    }
                    else if (availability == MEETING_ROOM_AVAILABLE_SOON)
                    {
                        return MEETING_ROOM_AVAILABLE_SOON_STATE;
                    }
                    else if (availability == MEETING_ROOM_OCCUPIED)
                    {
                        return MEETING_ROOM_OCCUPIED_STATE;
                    }

                    return MEETING_ROOM_AVAILABLE_STATE;
                }
            }
        }
    }
}