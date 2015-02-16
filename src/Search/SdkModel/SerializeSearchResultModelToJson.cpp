// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "Types.h"
#include "SearchResultModel.h"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            std::string SerializeToJson(const SearchResultModel& searchResult)
            {
                rapidjson::Document jsonDoc;
                rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                rapidjson::Value valueObject(rapidjson::kObjectType);
                
                valueObject.AddMember("id", searchResult.GetIdentifier().c_str(), allocator);
                valueObject.AddMember("title", searchResult.GetTitle().c_str(), allocator);
                valueObject.AddMember("address", searchResult.GetAddress().c_str(), allocator);
                valueObject.AddMember("phone", searchResult.GetPhone().c_str(), allocator);
                valueObject.AddMember("web", searchResult.GetWebUrl().c_str(), allocator);
                valueObject.AddMember("category", searchResult.GetCategory().c_str(), allocator);
                valueObject.AddMember("vicinity", searchResult.GetVicinity().c_str(), allocator);
                valueObject.AddMember("latitude", searchResult.GetLocation().GetLatitudeInDegrees(), allocator);
                valueObject.AddMember("longitude", searchResult.GetLocation().GetLongitudeInDegrees(), allocator);
               
                rapidjson::StringBuffer strbuf;
                rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                valueObject.Accept(writer);
                return strbuf.GetString();
            }
            
            SearchResultModel DeserializeFromJson(const std::string& searchResultJson)
            {
                rapidjson::Document document;
                
                const bool successfullyParsed = !(document.Parse<0>(searchResultJson.c_str()).HasParseError());
                
                Eegeo_ASSERT(successfullyParsed, "Failed to parse search result model JSON.\n");
                
                return SearchResultModel(document["id"].GetString(),
                                         document["title"].GetString(),
                                         Eegeo::Space::LatLong::FromDegrees(document["latitude"].GetDouble(),
                                                                            document["longitude"].GetDouble()),
                                         document["phone"].GetString(),
                                         document["address"].GetString(),
                                         document["web"].GetString(),
                                         document["category"].GetString(),
                                         document["vicinity"].GetString());
            }
        }
    }
}
