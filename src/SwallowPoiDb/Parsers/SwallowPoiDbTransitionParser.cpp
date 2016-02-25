// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SwallowPoiDbTransitionParser.h"

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
                poi_interior_id,
                poi_interior_floor,
                poi_latitude_degrees,
                poi_longitude_degrees,
                poi_target_interior_id,
                poi_target_interior_floor,
                poi_target_latitude_degrees,
                poi_target_longitude_degrees,
                PoiColumnIndices_MAX
            };
            
            Search::SdkModel::SearchResultModel SwallowPoiDbTransitionParser::SQLiteResultRowToSearchResult(const Eegeo::SQLite::SQLiteResultRow& resultRow, const std::string& assetsBaseUrl, int columnOffset)
            {
                rapidjson::Document jsonDoc;
                rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                rapidjson::Value valueObject(rapidjson::kObjectType);
                
				const std::string targetInteriorId(resultRow.Cell(columnOffset + poi_target_interior_id).AsText());

                AddStringToJson(Search::Swallow::SearchConstants::TARGET_INTERIOR_ID_FIELD_NAME,
								targetInteriorId,
								allocator,
								valueObject);
                
                valueObject.AddMember(Search::Swallow::SearchConstants::TARGET_INTERIOR_FLOOR_FIELD_NAME.c_str(),
                                      resultRow.Cell(columnOffset + poi_target_interior_floor).AsInteger(),
                                      allocator);
                
                valueObject.AddMember(Search::Swallow::SearchConstants::TARGET_LATITUDE_DEGREES_FIELD_NAME.c_str(),
                                      resultRow.Cell(columnOffset + poi_target_latitude_degrees).AsReal(),
                                      allocator);
                
                valueObject.AddMember(Search::Swallow::SearchConstants::TARGET_LONGITUDE_DEGREES_FILED_NAME.c_str(),
                                      resultRow.Cell(columnOffset + poi_target_longitude_degrees).AsReal(),
                                      allocator);
                
                rapidjson::StringBuffer strbuf;
                rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                valueObject.Accept(writer);

                std::string modelID = Search::Swallow::SearchConstants::TRANSITION_CATEGORY_NAME + std::string("_") + resultRow.Cell(columnOffset + poi_id).AsText();
                Eegeo::Space::LatLong modelLocation = Eegeo::Space::LatLong::FromDegrees(resultRow.Cell(columnOffset + poi_latitude_degrees).AsReal(), resultRow.Cell(columnOffset + poi_longitude_degrees).AsReal());
                
                Eegeo::Resources::Interiors::InteriorId interiorID = Eegeo::Resources::Interiors::InteriorId(resultRow.Cell(columnOffset + poi_interior_id).AsText());
                int interiorFloor = resultRow.Cell(columnOffset + poi_interior_floor).AsInteger();
                
                return Search::SdkModel::SearchResultModel(ExampleApp::Search::SdkModel::SearchResultModel::CurrentVersion,
                                                           modelID,
                                                           "",
                                                           "",
                                                           modelLocation,
                                                           0.0f,
                                                           true,
                                                           interiorID,
                                                           interiorFloor,
                                                           Search::Swallow::SearchConstants::TRANSITION_CATEGORY_NAME,
                                                           std::vector<std::string>(),
                                                           Search::EegeoVendorName,
														   strbuf.GetString(),
                                                           Eegeo::Helpers::Time::MillisecondsSinceEpoch());
            }
            
            Search::SdkModel::SearchResultModel SwallowPoiDbTransitionParser::SQLiteResultRowToSearchResult(const Eegeo::SQLite::SQLiteResultRow& resultRow, const std::string& assetsBaseUrl)
            {
                return SQLiteResultRowToSearchResult(resultRow, assetsBaseUrl, FtsQueryColumnIndices_MAX);
            }
        }
    }
}
