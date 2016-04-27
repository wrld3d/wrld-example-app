//
//  LaxSearchParser.cpp
//  ProjectLaxApp
//
//  Created by Kimble Operations on 28/09/2015.
//  Copyright (c) 2015 eeGeo. All rights reserved.
//

#include "LaxSearchParser.h"

#include <sstream>

#include "document.h"
#include "InteriorId.h"
#include "LatLongAltitude.h"
#include "stringbuffer.h"
#include "TimeHelpers.h"
#include "writer.h"

#include "SearchResultModel.h"
#include "SearchVendorNames.h"
#include "LaxSearchConstants.h"

#include "EegeoJsonParser.h"
#import "AppHost.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Lax
        {
            namespace SdkModel
            {
                namespace SearchParser
                {
                    
                    std::string GetFormattedAvailabilityString(const std::string& availabilityString)
                    {
                        if(availabilityString == Search::Lax::SearchConstants::MEETING_ROOM_AVAILABLE)
                        {
                            return "Available";
                        }
                        else if(availabilityString == Search::Lax::SearchConstants::MEETING_ROOM_AVAILABLE_SOON)
                        {
                            return "Available Soon";
                        }
                        else if(availabilityString == Search::Lax::SearchConstants::MEETING_ROOM_OCCUPIED)
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
                                                                   Search::Lax::SearchConstants::MEETING_ROOM_CATEGORY_NAME,
                                                                   std::vector<std::string>(),
                                                                   Search::EegeoVendorName,
                                                                   strbuf.GetString(),
                                                                   searchResultModel.GetCreationTimestamp());
                    }
                    
                    LaxMeetingRoomResultModel TransformToLaxMeetingRoomResult(const Search::SdkModel::SearchResultModel& searchResultModel)
                    {
                        rapidjson::Document json;
                        
//                        std::string imageUrl = "https://www.tscmamerica.com/wp-content/uploads/2015/10/033867392-meeting-room-interior-luxury-h-200x200.png";
                        std::string imageUrl = "";
                        std::string availability = "";//AppHost::GetMeetingRoomState(searchResultModel.GetTitle());
                        
                        TryParseImageDetails(searchResultModel, imageUrl);

//Using Local Device for persistance [QS]
//                        if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
//                        {
//                            if(json.HasMember(SearchConstants::AVAILABILITY_FIELD_NAME.c_str()) && json[SearchConstants::AVAILABILITY_FIELD_NAME.c_str()].IsString())
//                            {
//                                availability = json[SearchConstants::AVAILABILITY_FIELD_NAME.c_str()].GetString();
//                            }
//                        }
                        ///

                        return LaxMeetingRoomResultModel(searchResultModel.GetTitle(),
                                                             imageUrl,
                                                             availability);
                    }                    
                    
                    LaxTransitionResultModel TransformToLaxTransitionResult(const Search::SdkModel::SearchResultModel& searchResultModel)
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
                            Eegeo_ASSERT(false, "JSON parse error transforming search result model to Lax transition model");
                        }
                        
                        return LaxTransitionResultModel(Eegeo::Resources::Interiors::InteriorId(targetInteriorID),
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