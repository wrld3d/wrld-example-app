//
//  SwallowSearchParser.cpp
//  ProjectSwallowApp
//
//  Created by Kimble Operations on 28/09/2015.
//  Copyright (c) 2015 eeGeo. All rights reserved.
//

#include "SwallowSearchParser.h"

#include <sstream>

#include "document.h"
#include "InteriorId.h"
#include "LatLongAltitude.h"
#include "stringbuffer.h"
#include "TimeHelpers.h"
#include "writer.h"

#include "SearchResultModel.h"
#include "SearchVendorNames.h"
#include "SwallowSearchConstants.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Swallow
        {
            namespace SdkModel
            {
                namespace SearchParser
                {
                    SwallowPersonResultModel TransformToSwallowPersonResult(const Search::SdkModel::SearchResultModel& searchResultModel)
                    {
                        rapidjson::Document json;
                        
                        std::string name;
                        std::string jobTitle;
                        std::string imageFilename;
                        std::string workingGroup;
                        std::string officeLocation;
                        std::string deskCode;
                        
                        if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                        {
                            if(json.HasMember(SearchConstants::NAME_FIELD_NAME.c_str()) && json[SearchConstants::NAME_FIELD_NAME.c_str()].IsString())
                            {
                                name = json[SearchConstants::NAME_FIELD_NAME.c_str()].GetString();
                            }
                            
                            if(json.HasMember(SearchConstants::JOB_TITLE_FIELD_NAME.c_str()) && json[SearchConstants::JOB_TITLE_FIELD_NAME.c_str()].IsString())
                            {
                                jobTitle = json[SearchConstants::JOB_TITLE_FIELD_NAME.c_str()].GetString();
                            }
                            
                            if(json.HasMember(SearchConstants::IMAGE_FILENAME_FIELD_NAME.c_str()) && json[SearchConstants::IMAGE_FILENAME_FIELD_NAME.c_str()].IsString())
                            {
                                imageFilename = json[SearchConstants::IMAGE_FILENAME_FIELD_NAME.c_str()].GetString();
                            }
                            
                            if(json.HasMember(SearchConstants::WORKING_GROUP_FIELD_NAME.c_str()) && json[SearchConstants::WORKING_GROUP_FIELD_NAME.c_str()].IsString())
                            {
                                workingGroup = json[SearchConstants::WORKING_GROUP_FIELD_NAME.c_str()].GetString();
                            }
                            
                            if(json.HasMember(SearchConstants::OFFICE_LOCATION_FIELD_NAME.c_str()) && json[SearchConstants::OFFICE_LOCATION_FIELD_NAME.c_str()].IsString())
                            {
                                officeLocation = json[SearchConstants::OFFICE_LOCATION_FIELD_NAME.c_str()].GetString();
                            }
                            
                            if(json.HasMember(SearchConstants::DESK_CODE_FIELD_NAME.c_str()) && json[SearchConstants::DESK_CODE_FIELD_NAME.c_str()].IsString())
                            {
                                deskCode = json[SearchConstants::DESK_CODE_FIELD_NAME.c_str()].GetString();
                            }
                        }
                        else
                        {
                            Eegeo_ASSERT(false, "JSON parse error transforming search result model to swallow person model");
                        }
                        
                        return SwallowPersonResultModel(name,
                                                        jobTitle,
                                                        imageFilename,
                                                        workingGroup,
                                                        officeLocation,
                                                        deskCode);
                    }
                    
                    SwallowMeetingRoomResultModel TransformToSwallowMeetingRoomResult(const Search::SdkModel::SearchResultModel& searchResultModel)
                    {
                        rapidjson::Document json;
                        
                        std::string name;
                        std::string imageUrl;
                        std::string availability;
                        
                        if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                        {
                            if(json.HasMember(SearchConstants::NAME_FIELD_NAME.c_str()) && json[SearchConstants::NAME_FIELD_NAME.c_str()].IsString())
                            {
                                name = json[SearchConstants::NAME_FIELD_NAME.c_str()].GetString();
                            }
                            
                            if(json.HasMember(SearchConstants::IMAGE_FILENAME_FIELD_NAME.c_str()) && json[SearchConstants::IMAGE_FILENAME_FIELD_NAME.c_str()].IsString())
                            {
                                imageUrl = json[SearchConstants::IMAGE_FILENAME_FIELD_NAME.c_str()].GetString();
                            }
                            
                            if(json.HasMember(SearchConstants::AVAILABILITY_FIELD_NAME.c_str()) && json[SearchConstants::AVAILABILITY_FIELD_NAME.c_str()].IsString())
                            {
                                availability = json[SearchConstants::AVAILABILITY_FIELD_NAME.c_str()].GetString();
                            }
                        }
                        else
                        {
                            Eegeo_ASSERT(false, "JSON parse error transforming search result model to swallow meeting room model");
                        }
                        
                        return SwallowMeetingRoomResultModel(name,
                                                             imageUrl,
                                                             availability);
                    }
                    
                    SwallowWorkingGroupResultModel TransformToSwallowWorkingGroupResult(const Search::SdkModel::SearchResultModel& searchResultModel)
                    {
                        rapidjson::Document json;
                        
                        std::string name;
                        std::string imageUrl;
                        std::string description;
                        
                        if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                        {
                            if(json.HasMember(SearchConstants::NAME_FIELD_NAME.c_str()) && json[SearchConstants::NAME_FIELD_NAME.c_str()].IsString())
                            {
                                name = json[SearchConstants::NAME_FIELD_NAME.c_str()].GetString();
                            }
                            
                            if(json.HasMember(SearchConstants::IMAGE_FILENAME_FIELD_NAME.c_str()) && json[SearchConstants::IMAGE_FILENAME_FIELD_NAME.c_str()].IsString())
                            {
                                imageUrl = json[SearchConstants::IMAGE_FILENAME_FIELD_NAME.c_str()].GetString();
                            }
                            
                            if(json.HasMember(SearchConstants::DESCRIPTION_FIELD_NAME.c_str()) && json[SearchConstants::DESCRIPTION_FIELD_NAME.c_str()].IsString())
                            {
                                description = json[SearchConstants::DESCRIPTION_FIELD_NAME.c_str()].GetString();
                            }
                        }
                        else
                        {
                            Eegeo_ASSERT(false, "JSON parse error transforming search result model to swallow working group model");
                        }
                        
                        return SwallowWorkingGroupResultModel(name,
                                                              imageUrl,
                                                              description);
                    }
                    
                    SwallowFacilityResultModel TransformToSwallowFacilityResult(const Search::SdkModel::SearchResultModel& searchResultModel)
                    {
                        rapidjson::Document json;
                        
                        std::string name;
                        std::string imageUrl;
                        std::string description;
                        
                        if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                        {
                            if(json.HasMember(SearchConstants::NAME_FIELD_NAME.c_str()) && json[SearchConstants::NAME_FIELD_NAME.c_str()].IsString())
                            {
                                name = json[SearchConstants::NAME_FIELD_NAME.c_str()].GetString();
                            }
                            
                            if(json.HasMember(SearchConstants::IMAGE_FILENAME_FIELD_NAME.c_str()) && json[SearchConstants::IMAGE_FILENAME_FIELD_NAME.c_str()].IsString())
                            {
                                imageUrl = json[SearchConstants::IMAGE_FILENAME_FIELD_NAME.c_str()].GetString();
                            }
                            
                            if(json.HasMember(SearchConstants::DESCRIPTION_FIELD_NAME.c_str()) && json[SearchConstants::DESCRIPTION_FIELD_NAME.c_str()].IsString())
                            {
                                description = json[SearchConstants::DESCRIPTION_FIELD_NAME.c_str()].GetString();
                            }
                        }
                        else
                        {
                            Eegeo_ASSERT(false, "JSON parse error transforming search result model to swallow working group model");
                        }
                        
                        return SwallowFacilityResultModel(name,
                                                          imageUrl,
                                                          description);
                    }
                    
                    SwallowOfficeResultModel TransformToSwallowOfficeResult(const Search::SdkModel::SearchResultModel& searchResultModel)
                    {
                        rapidjson::Document json;
                        
                        std::string name;
                        float distance = 0.0f;
                        float headingDegrees = 0.0f;
                        
                        if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                        {
                            if(json.HasMember(SearchConstants::NAME_FIELD_NAME.c_str()) && json[SearchConstants::NAME_FIELD_NAME.c_str()].IsString())
                            {
                                name = json[SearchConstants::NAME_FIELD_NAME.c_str()].GetString();
                            }
                            
                            if(json.HasMember(SearchConstants::DISTANCE_FIELD_NAME.c_str()) && json[SearchConstants::DISTANCE_FIELD_NAME.c_str()].IsNumber())
                            {
                                distance = (float)json[SearchConstants::DISTANCE_FIELD_NAME.c_str()].GetDouble();
                            }
                            
                            if(json.HasMember(SearchConstants::HEADING_DEGREES_FIELD_NAME.c_str()) && json[SearchConstants::HEADING_DEGREES_FIELD_NAME.c_str()].IsNumber())
                            {
                                headingDegrees = (float)json[SearchConstants::HEADING_DEGREES_FIELD_NAME.c_str()].GetDouble();
                            }
                        }
                        else
                        {
                            Eegeo_ASSERT(false, "JSON parse error transforming search result model to swallow working group model");
                        }
                        
                        return SwallowOfficeResultModel(name,
                                                        distance,
                                                        headingDegrees);
                    }
                }
            }
        }
    }
}