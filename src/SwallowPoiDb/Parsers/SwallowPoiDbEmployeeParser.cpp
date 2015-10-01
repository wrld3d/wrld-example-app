// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SwallowPoiDbEmployeeParser.h"

#include "document.h"
#include "InteriorId.h"
#include "LatLongAltitude.h"
#include "SQLiteCellValue.h"
#include "SQLiteResultRow.h"
#include "stringbuffer.h"
#include "TimeHelpers.h"
#include "writer.h"

#include "SearchResultModel.h"
#include "SearchVendorNames.h"
#include "SwallowPoiDbParseHelper.h"
#include "SwallowSearchConstants.h"

namespace ExampleApp
{
    namespace SwallowPoiDb
    {
        namespace Parsers
        {
            enum PoiColumnIndices
            {
                poi_id = 0,
                poi_name,
                poi_job_title,
                poi_image_filename,
                poi_workingGroup,
                poi_office_location,
                poi_desk_code,
                poi_interior_id,
                poi_interior_floor,
                poi_latitude_degrees,
                poi_longitude_degrees,
                PoiColumnIndices_MAX
            };
            
            Search::SdkModel::SearchResultModel SwallowPoiDbEmployeeParser::SQLiteResultRowToSearchResult(const Eegeo::SQLite::SQLiteResultRow& resultRow, const std::string& assetsBaseUrl, int columnOffset)
            {
                rapidjson::Document jsonDoc;
                rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                rapidjson::Value valueObject(rapidjson::kObjectType);
                
                valueObject.AddMember(Search::Swallow::SearchConstants::NAME_FIELD_NAME.c_str(),
                                      resultRow.Cell(columnOffset + poi_name).AsText().c_str(),
                                      allocator);
                
                valueObject.AddMember(Search::Swallow::SearchConstants::JOB_TITLE_FIELD_NAME.c_str(),
                                      resultRow.Cell(columnOffset + poi_job_title).AsText().c_str(),
                                      allocator);
                
                valueObject.AddMember(Search::Swallow::SearchConstants::IMAGE_FILENAME_FIELD_NAME.c_str(),
                                      GetImageUrl(assetsBaseUrl, resultRow.Cell(columnOffset + poi_image_filename).AsText()).c_str(),
                                      allocator);
                
                valueObject.AddMember(Search::Swallow::SearchConstants::WORKING_GROUP_FIELD_NAME.c_str(),
                                      resultRow.Cell(columnOffset + poi_workingGroup).AsText().c_str(),
                                      allocator);
                
                valueObject.AddMember(Search::Swallow::SearchConstants::OFFICE_LOCATION_FIELD_NAME.c_str(),
                                      resultRow.Cell(columnOffset + poi_office_location).AsText().c_str(),
                                      allocator);
                
                valueObject.AddMember(Search::Swallow::SearchConstants::DESK_CODE_FIELD_NAME.c_str(),
                                      resultRow.Cell(columnOffset + poi_desk_code).AsText().c_str(),
                                      allocator);
                
                rapidjson::StringBuffer strbuf;
                rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                valueObject.Accept(writer);
                
                std::string modelID = Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME + std::string("_") + resultRow.Cell(columnOffset + poi_id).AsText();
                Eegeo::Space::LatLong modelLocation = Eegeo::Space::LatLong::FromDegrees(resultRow.Cell(columnOffset + poi_latitude_degrees).AsReal(), resultRow.Cell(columnOffset + poi_longitude_degrees).AsReal());
                
                
                return Search::SdkModel::SearchResultModel(ExampleApp::Search::SdkModel::SearchResultModel::CurrentVersion,
                                                           modelID,
                                                           resultRow.Cell(columnOffset + poi_name).AsText(),
                                                           resultRow.Cell(columnOffset + poi_job_title).AsText(),
                                                           modelLocation,
                                                           0.0f,
                                                           true,
                                                           Eegeo::Resources::Interiors::InteriorId(resultRow.Cell(columnOffset + poi_interior_id).AsText()),
                                                           resultRow.Cell(columnOffset + poi_interior_floor).AsInteger(),
                                                           Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME,
                                                           std::vector<std::string>(),
                                                           Search::SwallowPeopleVendorName,
                                                           strbuf.GetString(),
                                                           Eegeo::Helpers::Time::MillisecondsSinceEpoch());
            }
            
            Search::SdkModel::SearchResultModel SwallowPoiDbEmployeeParser::SQLiteResultRowToSearchResult(const Eegeo::SQLite::SQLiteResultRow& resultRow, const std::string& assetsBaseUrl)
            {
                return SQLiteResultRowToSearchResult(resultRow, assetsBaseUrl, FtsQueryColumnIndices_MAX);
            }
        }
    }
}
