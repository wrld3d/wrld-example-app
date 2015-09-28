// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include <vector>
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
            namespace
            {
                std::string ExtractAnyVersion4Data(rapidjson::Document& document)
                {
                    rapidjson::Document jsonDoc;
                    rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                    rapidjson::Value valueObject(rapidjson::kObjectType);
                    std::string jsonString ="";
                    
                    if(document.HasMember("phone") && std::string(document["phone"].GetString()).empty() == false)
                    {
                        valueObject.AddMember("display_phone", document["phone"].GetString(), allocator);
                    }
                    if(document.HasMember("web") && std::string(document["web"].GetString()).empty() == false)
                    {
                        valueObject.AddMember("url", document["web"].GetString(), allocator);
                    }
                    if(document.HasMember("imageUrl") && std::string(document["imageUrl"].GetString()).empty() == false)
                    {
                        valueObject.AddMember("image_url", document["imageUrl"].GetString(), allocator);
                    }
                    if(document.HasMember("ratingImageUrl") && std::string(document["ratingImageUrl"].GetString()).empty() == false)
                    {
                        valueObject.AddMember("rating", document["ratingImageUrl"].GetString(), allocator);
                    }
                    if(document.HasMember("reviews"))
                    {
                        const rapidjson::Value& reviewsJson(document["reviews"]);
                        if(reviewsJson.Size() > 0)
                        {
                            rapidjson::SizeType index = 0;
                            valueObject.AddMember("snippet_text", reviewsJson[index].GetString(), allocator);
                        }
                    }
                    if(document.HasMember("reviewCount"))
                    {
                        valueObject.AddMember("review_count", document["reviewCount"].GetInt(), allocator);
                    }
                    
                    rapidjson::StringBuffer strbuf;
                    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                    valueObject.Accept(writer);
                    return strbuf.GetString();
                }
            }
            std::string SerializeToJson(const SearchResultModel& searchResult)
            {
                rapidjson::Document jsonDoc;
                rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                rapidjson::Value valueObject(rapidjson::kObjectType);
                
                rapidjson::Value categoriesJson(rapidjson::kArrayType);
                const std::vector<std::string>& categories(searchResult.GetHumanReadableCategories());
                for(std::vector<std::string>::const_iterator it = categories.begin(); it != categories.end(); ++ it)
                {
                    categoriesJson.PushBack(it->c_str(), allocator);
                }
                
                valueObject.AddMember("version", searchResult.GetVersion(), allocator);
                valueObject.AddMember("id", searchResult.GetIdentifier().c_str(), allocator);
                valueObject.AddMember("title", searchResult.GetTitle().c_str(), allocator);
                valueObject.AddMember("subtitle", searchResult.GetSubtitle().c_str(), allocator);
                valueObject.AddMember("interior", searchResult.IsInterior(), allocator);
                valueObject.AddMember("building", searchResult.GetBuildingId().Value().c_str(), allocator);
                valueObject.AddMember("floor", searchResult.GetFloor(), allocator);
                valueObject.AddMember("category", searchResult.GetCategory().c_str(), allocator);
                valueObject.AddMember("humanReadableCategories", categoriesJson, allocator);
                valueObject.AddMember("vendor", searchResult.GetVendor().c_str(), allocator);
                valueObject.AddMember("latitude", searchResult.GetLocation().GetLatitudeInDegrees(), allocator);
                valueObject.AddMember("longitude", searchResult.GetLocation().GetLongitudeInDegrees(), allocator);
                valueObject.AddMember("heightAboveTerrain", searchResult.GetHeightAboveTerrainMetres(), allocator);
                valueObject.AddMember("json", searchResult.GetJsonData().c_str(), allocator);
                valueObject.AddMember("createTimestamp", searchResult.GetCreationTimestamp(), allocator);
                
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
                
                Eegeo_ASSERT(document.HasMember("version"),
                             "Old SearchResultModel version detected. Please delete and reinstall the application.\n");
                
                int version = document["version"].GetInt();
                
                const int earliestSupportedVersionForUpversioning = 4;
                
                Eegeo_ASSERT(version >= earliestSupportedVersionForUpversioning,
                             "Old SearchResultModel version detected: tried to deserialize version %d but current version is %d. Please delete and reinstall the application.\n", version, SearchResultModel::CurrentVersion);
                
                std::string jsonData = "";
                if(version == 4)
                {
                    jsonData = ExtractAnyVersion4Data(document);
                    version = SearchResultModel::CurrentVersion;
                }
                else if(version > 4)
                {
                    jsonData = document["json"].GetString();
                }
                
                const rapidjson::Value& categoriesJson(document["humanReadableCategories"]);
                std::vector<std::string> categories;
                for(rapidjson::SizeType i = 0; i < categoriesJson.Size(); ++ i)
                {
                    categories.push_back(categoriesJson[i].GetString());
                }
                
                bool interior = false;
                if(document.HasMember("interior"))
                {
                    interior = document["interior"].GetBool();
                }
                
                std::string building = "";
                if(document.HasMember("building"))
                {
                    building = document["building"].GetString();
                }
        
                int floor = 0;
                if(document.HasMember("floor"))
                {
                    floor = document["floor"].GetInt();
                }
                
                float heightAboveTerrainMetres = 0;
                if(document.HasMember("heightAboveTerrain"))
                {
                    heightAboveTerrainMetres = static_cast<float>(document["heightAboveTerrain"].GetDouble());
                }
                
                return SearchResultModel(version,
                                         document["id"].GetString(),
                                         document["title"].GetString(),
                                         document.HasMember("address") ? document["address"].GetString() : document["subtitle"].GetString(),
                                         Eegeo::Space::LatLong::FromDegrees(document["latitude"].GetDouble(),
                                                                            document["longitude"].GetDouble()),
                                         heightAboveTerrainMetres,
                                         interior,
                                         building,
                                         floor,
                                         document["category"].GetString(),
                                         categories,
                                         document["vendor"].GetString(),
                                         jsonData,
                                         document["createTimestamp"].GetInt64());
            }
        }
    }
}
