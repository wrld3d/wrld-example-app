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
                const std::string CATEGORY_FIELD_NAME = "category";
                const std::string DISTANCE_FIELD_NAME = "distance";
                const std::string HEADING_DEGREES_FIELD_NAME = "heading_degrees";
                
                extern const std::string PERSON_CATEGORY_NAME = "person";
                extern const std::string MEETING_ROOM_CATEGORY_NAME = "meeting_room";
                extern const std::string WORKING_GROUP_CATEGORY_NAME = "working_group";
                extern const std::string FACILITY_CATEGORY_NAME = "facility";
                extern const std::string OFFICE_CATEGORY_NAME = "office";
                
                std::vector<CategorySearch::View::CategorySearchModel> GetCategorySearchModels()
                {
                    const bool showCategoriesInSearchMenu = false;
                    
                    std::vector<ExampleApp::CategorySearch::View::CategorySearchModel> categories;
                    
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Meeting Rooms", MEETING_ROOM_CATEGORY_NAME, MEETING_ROOM_CATEGORY_NAME, showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Working Groups", WORKING_GROUP_CATEGORY_NAME, WORKING_GROUP_CATEGORY_NAME, showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Facilities", FACILITY_CATEGORY_NAME, FACILITY_CATEGORY_NAME, showCategoriesInSearchMenu));
                    categories.push_back(ExampleApp::CategorySearch::View::CategorySearchModel("Offices", OFFICE_CATEGORY_NAME, OFFICE_CATEGORY_NAME, showCategoriesInSearchMenu));
                    
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
            }
        }
    }
}