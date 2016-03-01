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

#include "EegeoJsonParser.h"

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
                        
                        std::string workingGroup;
                        std::string officeLocation;
                        std::string deskCode;
                        std::string imageUrl;
                        
                        TryParseImageDetails(searchResultModel, imageUrl);
                        if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                        {
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
                        
                        return SwallowPersonResultModel(searchResultModel.GetTitle(),
                                                        searchResultModel.GetSubtitle(),
                                                        imageUrl,
                                                        workingGroup,
                                                        officeLocation,
                                                        deskCode);
                    }
                    
                    std::string GetFormattedAvailabilityString(const std::string& availabilityString)
                    {
                        if(availabilityString == Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE)
                        {
                            return "Available";
                        }
                        else if(availabilityString == Search::Swallow::SearchConstants::MEETING_ROOM_AVAILABLE_SOON)
                        {
                            return "Available Soon";
                        }
                        else if(availabilityString == Search::Swallow::SearchConstants::MEETING_ROOM_OCCUPIED)
                        {
                            return "Occupied";
                        }
                        else
                        {
                            Eegeo_ASSERT(false, "Unrecognised meeting room availabity string");
                            return "Unknown";
                        }
                    }
                    
                    ExampleApp::Search::SdkModel::SearchResultModel MutateMeetingRoomAvailability(const Search::SdkModel::SearchResultModel& searchResultModel, const std::string& updatedAvailability)
                    {
                        rapidjson::Document json;
                        if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                        {
                            json[SearchConstants::AVAILABILITY_FIELD_NAME.c_str()] = rapidjson::Value(updatedAvailability.c_str(), json.GetAllocator()).Move();
                        }
                        
                        rapidjson::StringBuffer strbuf;
                        rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                        json.Accept(writer);
                        
                        return Search::SdkModel::SearchResultModel(ExampleApp::Search::SdkModel::SearchResultModel::CurrentVersion,
                                                                   searchResultModel.GetIdentifier(),
                                                                   searchResultModel.GetTitle(),
                                                                   searchResultModel.GetSubtitle(),
                                                                   searchResultModel.GetLocation(),
                                                                   0.0f,
                                                                   true,
                                                                   searchResultModel.GetBuildingId(),
                                                                   searchResultModel.GetFloor(),
                                                                   Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME,
                                                                   std::vector<std::string>(),
                                                                   Search::EegeoVendorName,
                                                                   strbuf.GetString(),
                                                                   searchResultModel.GetCreationTimestamp());
                    }
                    
                    SwallowMeetingRoomResultModel TransformToSwallowMeetingRoomResult(const Search::SdkModel::SearchResultModel& searchResultModel)
                    {
                        rapidjson::Document json;
                        
                        std::string imageUrl;
                        std::string availability = "available";
                        
                        TryParseImageDetails(searchResultModel, imageUrl);
                        if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                        {
                            if(json.HasMember(SearchConstants::AVAILABILITY_FIELD_NAME.c_str()) && json[SearchConstants::AVAILABILITY_FIELD_NAME.c_str()].IsString())
                            {
                                availability = json[SearchConstants::AVAILABILITY_FIELD_NAME.c_str()].GetString();
                            }
                        }
                        
                        return SwallowMeetingRoomResultModel(searchResultModel.GetTitle(),
                                                             imageUrl,
                                                             availability);
                    }
                    
                    SwallowWorkingGroupResultModel TransformToSwallowWorkingGroupResult(const Search::SdkModel::SearchResultModel& searchResultModel)
                    {
                        std::string imageUrl;
                        TryParseImageDetails(searchResultModel, imageUrl);
                        rapidjson::Document json;
                        std::string description;
                        if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                        {
                            if(json.HasMember(SearchConstants::DESCRIPTION_FIELD_NAME.c_str()) && json[SearchConstants::DESCRIPTION_FIELD_NAME.c_str()].IsString())
                            {
                                description = json[SearchConstants::DESCRIPTION_FIELD_NAME.c_str()].GetString();
                            }
                        }
                        return SwallowWorkingGroupResultModel(searchResultModel.GetTitle(),
                                                              imageUrl,
                                                              description);
                    }
                    
                    SwallowFacilityResultModel TransformToSwallowFacilityResult(const Search::SdkModel::SearchResultModel& searchResultModel)
                    {
                        std::string imageUrl;
                        TryParseImageDetails(searchResultModel, imageUrl);
                        rapidjson::Document json;
                        std::string description;
                        if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                        {
                            if(json.HasMember(SearchConstants::DESCRIPTION_FIELD_NAME.c_str()) && json[SearchConstants::DESCRIPTION_FIELD_NAME.c_str()].IsString())
                            {
                                description = json[SearchConstants::DESCRIPTION_FIELD_NAME.c_str()].GetString();
                            }
                        }
                        return SwallowFacilityResultModel(searchResultModel.GetTitle(),
                                                          imageUrl,
                                                          description);
                    }
                    
                    SwallowDepartmentResultModel TransformToSwallowDepartmentResult(const Search::SdkModel::SearchResultModel& searchResultModel)
                    {
                        std::string imageUrl;
                        TryParseImageDetails(searchResultModel, imageUrl);
                        rapidjson::Document json;
                        std::string description;
                        std::vector<std::string> desks;
                        if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                        {
                            if(json.HasMember(SearchConstants::DESCRIPTION_FIELD_NAME.c_str()) && json[SearchConstants::DESCRIPTION_FIELD_NAME.c_str()].IsString())
                            {
                                description = json[SearchConstants::DESCRIPTION_FIELD_NAME.c_str()].GetString();
                            }
                            
                            if(json.HasMember(SearchConstants::DESKS_FIELD_NAME.c_str()) && json[SearchConstants::DESKS_FIELD_NAME.c_str()].IsArray())
                            {
                                rapidjson::Value& deskJsonArray = json[SearchConstants::DESKS_FIELD_NAME.c_str()];
                                desks.reserve(deskJsonArray.Size());
                                for (rapidjson::SizeType i = 0; i < deskJsonArray.Size(); i++)
                                {
                                    if (deskJsonArray[i].IsString())
                                    {
                                        desks.push_back(deskJsonArray[i].GetString());
                                    }
                                }
                            }
                        }
                        return SwallowDepartmentResultModel(searchResultModel.GetTitle(),
                                                            imageUrl,
                                                            description,
                                                            desks);
                    }
                    
                    SwallowOfficeResultModel TransformToSwallowOfficeResult(const Search::SdkModel::SearchResultModel& searchResultModel)
                    {
                        rapidjson::Document json;
                        
                        float distance = 0.0f;
                        float headingDegrees = 0.0f;
                        
                        if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                        {
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
                        
                        return SwallowOfficeResultModel(searchResultModel.GetTitle(),
                                                        distance,
                                                        headingDegrees);
                    }
                    
                    SwallowTransitionResultModel TransformToSwallowTransitionResult(const Search::SdkModel::SearchResultModel& searchResultModel)
                    {
                        rapidjson::Document json;
                        
                        std::string targetInteriorID("");
                        int targetInteriorFloor = 0;
                        double targetLatitudeDegrees = 0.0;
                        double targetLongitudeDegrees = 0.0;
                        
                        if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                        {
                            if(json.HasMember(SearchConstants::TARGET_INTERIOR_ID_FIELD_NAME.c_str()) && json[SearchConstants::TARGET_INTERIOR_ID_FIELD_NAME.c_str()].IsString())
                            {
                                targetInteriorID = json[SearchConstants::TARGET_INTERIOR_ID_FIELD_NAME.c_str()].GetString();
                            }
                            
                            if(json.HasMember(SearchConstants::TARGET_INTERIOR_FLOOR_FIELD_NAME.c_str()) && json[SearchConstants::TARGET_INTERIOR_FLOOR_FIELD_NAME.c_str()].IsNumber())
                            {
                                targetInteriorFloor = json[SearchConstants::TARGET_INTERIOR_FLOOR_FIELD_NAME.c_str()].GetInt();
                            }
                            
                            if(json.HasMember(SearchConstants::TARGET_LATITUDE_DEGREES_FIELD_NAME.c_str()) && json[SearchConstants::TARGET_LATITUDE_DEGREES_FIELD_NAME.c_str()].IsNumber())
                            {
                                targetLatitudeDegrees = (float)json[SearchConstants::TARGET_LATITUDE_DEGREES_FIELD_NAME.c_str()].GetDouble();
                            }
                            
                            if(json.HasMember(SearchConstants::TARGET_LONGITUDE_DEGREES_FILED_NAME.c_str()) && json[SearchConstants::TARGET_LONGITUDE_DEGREES_FILED_NAME.c_str()].IsNumber())
                            {
                                targetLongitudeDegrees = (float)json[SearchConstants::TARGET_LONGITUDE_DEGREES_FILED_NAME.c_str()].GetDouble();
                            }
                        }
                        else
                        {
                            Eegeo_ASSERT(false, "JSON parse error transforming search result model to swallow transition model");
                        }
                        
                        return SwallowTransitionResultModel(Eegeo::Resources::Interiors::InteriorId(targetInteriorID),
                                                            targetInteriorFloor,
                                                            Eegeo::Space::LatLong::FromDegrees(targetLatitudeDegrees, targetLongitudeDegrees));
                    }
                    
                    bool TryParseImageDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_imageUrl)
                    {
                        return Search::EegeoPois::SdkModel::TryParseImageDetails(searchResultModel, out_imageUrl);
                    }
                }
            }
        }
    }
}