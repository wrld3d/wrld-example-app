// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SwallowPoiDbOfficeParser.h"

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
                poi_latitude_degrees,
                poi_longitude_degrees,
                poi_distance,
                poi_heading_degrees,
                PoiColumnIndices_MAX
            };
            
            Search::SdkModel::SearchResultModel SwallowPoiDbOfficeParser::SQLiteResultRowToSearchResult(const Eegeo::SQLite::SQLiteResultRow& resultRow, const std::string& assetsBaseUrl, int columnOffset)
            {
                rapidjson::Document jsonDoc;
                rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                rapidjson::Value valueObject(rapidjson::kObjectType);
                
                valueObject.AddMember(Search::Swallow::SearchConstants::NAME_FIELD_NAME.c_str(),
                                      resultRow.Cell(columnOffset + poi_name).AsText().c_str(),
                                      allocator);
                
                valueObject.AddMember(Search::Swallow::SearchConstants::DISTANCE_FIELD_NAME.c_str(),
                                      resultRow.Cell(columnOffset + poi_distance).AsReal(),
                                      allocator);
                
                valueObject.AddMember(Search::Swallow::SearchConstants::HEADING_DEGREES_FIELD_NAME.c_str(),
                                      resultRow.Cell(columnOffset + poi_heading_degrees).AsReal(),
                                      allocator);
                
                rapidjson::StringBuffer strbuf;
                rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                valueObject.Accept(writer);
                
                std::string modelID = Search::Swallow::SearchConstants::OFFICE_CATEGORY_NAME + std::string("_") + resultRow.Cell(columnOffset + poi_id).AsText();
                Eegeo::Space::LatLong modelLocation = Eegeo::Space::LatLong::FromDegrees(resultRow.Cell(columnOffset + poi_latitude_degrees).AsReal(), resultRow.Cell(columnOffset + poi_longitude_degrees).AsReal());
                
                return Search::SdkModel::SearchResultModel(ExampleApp::Search::SdkModel::SearchResultModel::CurrentVersion,
                                                           modelID,
                                                           resultRow.Cell(columnOffset + poi_name).AsText(),
                                                           "",
                                                           modelLocation,
                                                           0.0f,
                                                           false,
                                                           Eegeo::Resources::Interiors::InteriorId(),
                                                           0,
                                                           Search::Swallow::SearchConstants::OFFICE_CATEGORY_NAME,
                                                           std::vector<std::string>(),
                                                           Search::SwallowOfficesVendorName,
                                                           strbuf.GetString(),
                                                           Eegeo::Helpers::Time::MillisecondsSinceEpoch());
            }
            
            Search::SdkModel::SearchResultModel SwallowPoiDbOfficeParser::SQLiteResultRowToSearchResult(const Eegeo::SQLite::SQLiteResultRow& resultRow, const std::string& assetsBaseUrl)
            {
                return SQLiteResultRowToSearchResult(resultRow, assetsBaseUrl, FtsQueryColumnIndices_MAX);
            }
        }
    }
}
