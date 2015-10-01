// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SwallowPoiDbFacilityParser.h"

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
                poi_category,
                poi_image_filename,
                poi_description,
                poi_interior_id,
                poi_interior_floor,
                poi_latitude_degrees,
                poi_longitude_degrees,
                PoiColumnIndices_MAX
            };
            
            Search::SdkModel::SearchResultModel SwallowPoiDbFacilityParser::SQLiteResultRowToSearchResult(const Eegeo::SQLite::SQLiteResultRow& resultRow, const std::string& assetsBaseUrl, int columnOffset)
            {
                rapidjson::Document jsonDoc;
                rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                rapidjson::Value valueObject(rapidjson::kObjectType);
                
                valueObject.AddMember(Search::Swallow::SearchConstants::NAME_FIELD_NAME.c_str(),
                                      resultRow.Cell(columnOffset + poi_name).AsText().c_str(),
                                      allocator);
                
                valueObject.AddMember(Search::Swallow::SearchConstants::CATEGORY_FIELD_NAME.c_str(),
                                      resultRow.Cell(columnOffset + poi_category).AsText().c_str(),
                                      allocator);
                
                valueObject.AddMember(Search::Swallow::SearchConstants::IMAGE_FILENAME_FIELD_NAME.c_str(),
                                      GetImageUrl(assetsBaseUrl, resultRow.Cell(columnOffset + poi_image_filename).AsText()).c_str(),
                                      allocator);
                
                valueObject.AddMember(Search::Swallow::SearchConstants::DESCRIPTION_FIELD_NAME.c_str(),
                                      resultRow.Cell(columnOffset + poi_description).AsText().c_str(),
                                      allocator);
                
                rapidjson::StringBuffer strbuf;
                rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                valueObject.Accept(writer);
                
                return Search::SdkModel::SearchResultModel(ExampleApp::Search::SdkModel::SearchResultModel::CurrentVersion,
                                                           resultRow.Cell(columnOffset + poi_id).AsText(),
                                                           resultRow.Cell(columnOffset + poi_name).AsText(),
                                                           "",
                                                           Eegeo::Space::LatLong::FromDegrees(resultRow.Cell(columnOffset + poi_latitude_degrees).AsReal(), resultRow.Cell(columnOffset + poi_longitude_degrees).AsReal()),
                                                           0.0f,
                                                           true,
                                                           Eegeo::Resources::Interiors::InteriorId(resultRow.Cell(columnOffset + poi_interior_id).AsText()),
                                                           resultRow.Cell(columnOffset + poi_interior_floor).AsInteger(),
                                                           resultRow.Cell(columnOffset + poi_category).AsText(),
                                                           std::vector<std::string>(),
                                                           Search::SwallowFacilitiesVendorName,
                                                           strbuf.GetString(),
                                                           Eegeo::Helpers::Time::MillisecondsSinceEpoch());
            }
            
            Search::SdkModel::SearchResultModel SwallowPoiDbFacilityParser::SQLiteResultRowToSearchResult(const Eegeo::SQLite::SQLiteResultRow& resultRow, const std::string& assetsBaseUrl)
            {
                return SQLiteResultRowToSearchResult(resultRow, assetsBaseUrl, FtsQueryColumnIndices_MAX);
            }
        }
    }
}
