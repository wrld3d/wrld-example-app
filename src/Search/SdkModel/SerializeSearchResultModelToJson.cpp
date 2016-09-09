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
            std::string SerializeToJson(const SearchResultModel& searchResult)
            {
                rapidjson::Document jsonDoc;
                rapidjson::Document::AllocatorType& allocator = jsonDoc.GetAllocator();
                rapidjson::Value valueObject(rapidjson::kObjectType);
                
                rapidjson::Value humanReadableTagsJson(rapidjson::kArrayType);

                {
                    const std::vector<std::string>& humanReadableTags(searchResult.GetHumanReadableTags());
                    humanReadableTagsJson.Reserve(static_cast<rapidjson::SizeType>(humanReadableTags.size()), allocator);

                    for (const auto& v : humanReadableTags)
                    {
                        humanReadableTagsJson.PushBack(rapidjson::Value(v.c_str(), allocator).Move(), allocator);
                    }
                }

                rapidjson::Value tagsJson(rapidjson::kArrayType);

                {
                    const std::vector<std::string>& tags(searchResult.GetTags());
                    tagsJson.Reserve(static_cast<rapidjson::SizeType>(tags.size()), allocator);
                    for(const auto& v : tags)
                    {
                        tagsJson.PushBack(rapidjson::Value(v.c_str(), allocator).Move(), allocator);
                    }
                }

                valueObject.AddMember("version", searchResult.GetVersion(), allocator);
                valueObject.AddMember("id", rapidjson::Value(searchResult.GetIdentifier().c_str(), allocator).Move(), allocator);
                valueObject.AddMember("title", rapidjson::Value(searchResult.GetTitle().c_str(), allocator).Move(), allocator);
                valueObject.AddMember("subtitle", rapidjson::Value(searchResult.GetSubtitle().c_str(), allocator).Move(), allocator);
                valueObject.AddMember("interior", searchResult.IsInterior(), allocator);
                valueObject.AddMember("building", rapidjson::Value(searchResult.GetBuildingId().Value().c_str(), allocator).Move(), allocator);
                valueObject.AddMember("floor", searchResult.GetFloor(), allocator);

                valueObject.AddMember("tags", tagsJson, allocator);
                valueObject.AddMember("humanReadableTags", humanReadableTagsJson, allocator);
                valueObject.AddMember("iconKey", rapidjson::Value(searchResult.GetIconKey().c_str(), allocator).Move(), allocator);
                valueObject.AddMember("vendor", rapidjson::Value(searchResult.GetVendor().c_str(), allocator).Move(), allocator);
                valueObject.AddMember("latitude", searchResult.GetLocation().GetLatitudeInDegrees(), allocator);
                valueObject.AddMember("longitude", searchResult.GetLocation().GetLongitudeInDegrees(), allocator);
                valueObject.AddMember("heightAboveTerrain", searchResult.GetHeightAboveTerrainMetres(), allocator);
                valueObject.AddMember("json", rapidjson::Value(searchResult.GetJsonData().c_str(), allocator).Move(), allocator);
                valueObject.AddMember("createTimestamp", searchResult.GetCreationTimestamp(), allocator);
                
                rapidjson::StringBuffer strbuf;
                rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                valueObject.Accept(writer);
                return strbuf.GetString();
                
            }

            bool TryDeserializeFromJson(const std::string& searchResultJson, SearchResultModel& out_resultModel)
            {
                rapidjson::Document document;
                const bool successfullyParsed = !(document.Parse<0>(searchResultJson.c_str()).HasParseError());
                
                if(!successfullyParsed)
                {
                    Eegeo_TTY("Failed to parse search result model JSON.\n");
                    return false;
                }
                
                if(!document.HasMember("version"))
                {
                    Eegeo_TTY("Old SearchResultModel version detected. Please delete and reinstall the application.\n");
                    return false;
                }
                
                const int version = document["version"].GetInt();

                if(version != ExampleApp::Search::SdkModel::SearchResultModel::CurrentVersion)
                {
                    Eegeo_TTY("Old SearchResultModel version detected: tried to deserialize version %d but current version is %d. Please delete and reinstall the application.\n", version, SearchResultModel::CurrentVersion);
                    return false;
                }
                
                const std::string jsonData = document["json"].GetString();

                const bool interior = document.HasMember("interior") ?
                        document["interior"].GetBool() :
                        false;

                const std::string building = document.HasMember("building") ?
                        document["building"].GetString() :
                        "";

                const int floor = document.HasMember("floor") ?
                        document["floor"].GetInt() :
                        0;

                const float heightAboveTerrainMetres = document.HasMember("heightAboveTerrain") ?
                        static_cast<float>(document["heightAboveTerrain"].GetDouble())
                        : 0.0f;

                const Search::SdkModel::TagIconKey tagIconKey = document["iconKey"].GetString();

                std::vector<std::string> tags;

                {
                    const auto& tagsJson(document["tags"]);
                    tags.reserve(tagsJson.Size());
                    for (auto i = 0; i < tagsJson.Size(); ++i)
                    {
                        tags.push_back(tagsJson[i].GetString());
                    }
                }

                std::vector<std::string> humanReadableTags;

                {
                    const auto& humanReadableTagsJson(document["humanReadableTags"]);
                    humanReadableTags.reserve(humanReadableTagsJson.Size());
                    for (auto i = 0; i < humanReadableTagsJson.Size(); ++i)
                    {
                        humanReadableTags.push_back(humanReadableTagsJson[i].GetString());
                    }
                }

                const Eegeo::Space::LatLong& location = Eegeo::Space::LatLong::FromDegrees(
                        document["latitude"].GetDouble(),
                        document["longitude"].GetDouble());

                const std::string subtitle = document.HasMember("address") ?
                        document["address"].GetString() :
                        document["subtitle"].GetString();

                out_resultModel = SearchResultModel(version,
                                                    document["id"].GetString(),
                                                    document["title"].GetString(),
                                                    subtitle,
                                                    location,
                                                    heightAboveTerrainMetres,
                                                    interior,
                                                    building,
                                                    floor,
                                                    tags,
                                                    humanReadableTags,
                                                    tagIconKey,
                                                    document["vendor"].GetString(),
                                                    jsonData,
                                                    document["createTimestamp"].GetInt64());
                
                return true;
            }
        }
    }
}
