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

#include "PoiTableDto.h"
#include "SearchResultModel.h"
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
                    void ParsePersonSearchResults(const std::vector<PoiDb::PoiTableDto>& results,
                                                  std::vector<Search::SdkModel::SearchResultModel>& out_results)
                    {
                        for(int i = 0; i < results.size(); ++i)
                        {
                            rapidjson::Document jsonDoc;
                            rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                            rapidjson::Value valueObject(rapidjson::kObjectType);
                            
                            const PoiDb::PoiTableDto& result = results.at(i);
                            
                            valueObject.AddMember(SearchConstants::NAME_FIELD_NAME.c_str(), result.name.c_str(), allocator);
                            valueObject.AddMember(SearchConstants::JOB_TITLE_FIELD_NAME.c_str(), result.job_title.c_str(), allocator);
                            valueObject.AddMember(SearchConstants::WORKING_GROUP_FIELD_NAME.c_str(), result.working_group.c_str(), allocator);
                            valueObject.AddMember(SearchConstants::OFFICE_LOCATION_FIELD_NAME.c_str(), result.office_location.c_str(), allocator);
                            valueObject.AddMember(SearchConstants::DESK_CODE_FIELD_NAME.c_str(), result.desk_code.c_str(), allocator);
                            
                            rapidjson::StringBuffer strbuf;
                            rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                            valueObject.Accept(writer);
                            
                            std::stringstream idString;
                            idString << result.poi_id;
                            
                            out_results.push_back(Search::SdkModel::SearchResultModel(ExampleApp::Search::SdkModel::SearchResultModel::CurrentVersion,
                                                                                      idString.str(),
                                                                                      result.name,
                                                                                      result.job_title,
                                                                                      Eegeo::Space::LatLong::FromDegrees(result.latitude_degrees, result.longitude_degrees),
                                                                                      0.0f,
                                                                                      true,
                                                                                      Eegeo::Resources::Interiors::InteriorId(result.interior_id),
                                                                                      result.interior_floor,
                                                                                      "person",
                                                                                      std::vector<std::string>(),
                                                                                      "Swallow",
                                                                                      strbuf.GetString(),
                                                                                      Eegeo::Helpers::Time::MillisecondsSinceEpoch()));
                        }
                    }
                    
                    SwallowPersonResultModel TransformToSwallowPersonResult(const Search::SdkModel::SearchResultModel& searchResultModel)
                    {
                        rapidjson::Document json;
                        
                        std::string name;
                        std::string jobTitle;
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
                                                        workingGroup,
                                                        officeLocation,
                                                        deskCode);
                    }
                }
            }
        }
    }
}