// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoJsonParser.h"
#include "SearchVendorNames.h"
#include "TimeHelpers.h"
#include "InteriorId.h"
#include "EegeoReadableTagMapper.h"

#include "document.h"
#include "writer.h"
#include "stringbuffer.h"

#include <sstream>
#include <map>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                namespace
                {   
                    std::vector<std::string> SplitIntoTags(const std::string& str, char c)
                    {
                        std::vector<std::string> tags;
                        unsigned previous_start = -1;

                        for (unsigned i = 0; i < str.length(); ++i)
                        {
                            if (str[i] == c)
                            {
                                tags.push_back(str.substr(previous_start + 1, i - previous_start - 1));
                                previous_start = i;
                            }
                        }

                        if (previous_start != str.length() - 1)
                        {
                            tags.push_back(str.substr(previous_start + 1));
                        }

                        return tags;
                    }
                    
                    std::vector<std::string> GetNamesForTags(const std::vector<std::string>& tags, const EegeoReadableTagMapper& tagNameMapper)
                    {
                        std::vector<std::string> readableTags;
                        
                        for(std::vector<std::string>::const_iterator it = tags.begin(); it != tags.end(); ++it)
                        {
                            const std::string& tag = *it;
                            
                            readableTags.push_back(tagNameMapper.GetNameForTag(tag));
                        }
                        
                        return readableTags;
                     }

                    Search::SdkModel::SearchResultModel ParseSearchResultFromJsonObject(const rapidjson::Value& json,
                                                                                        const SearchResultPoi::SdkModel::ITagIconMapper& tagIconMapper,
                                                                                        const EegeoReadableTagMapper& tagNameMapper)
                    {
                        Eegeo::Space::LatLong location = Eegeo::Space::LatLong::FromDegrees(json["lat"].GetDouble(),
                                                                                            json["lon"].GetDouble());
                        
                        std::stringstream idStream;
                        idStream << json["id"].GetInt();
                        
                        bool indoor = json["indoor"].GetBool();
                        Eegeo::Resources::Interiors::InteriorId interiorId(json["indoor_id"].GetString());
                        
                        std::vector<std::string> tags = SplitIntoTags(json["tags"].GetString(), ' ');
                        std::vector<std::string> readableTags = GetNamesForTags(tags, tagNameMapper);

                        const Search::SdkModel::TagIconKey& tagIconKey = tagIconMapper.GetIconKeyForTags(tags);
                        
                        std::string userData = "";
                        
                        if (json.HasMember("user_data"))
                        {
                            rapidjson::StringBuffer strbuf;
                            rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                            json["user_data"].Accept(writer);
                            userData = strbuf.GetString();
                        }

                        return ExampleApp::Search::SdkModel::SearchResultModel(ExampleApp::Search::SdkModel::SearchResultModel::CurrentVersion,
                                                                               idStream.str(),
                                                                               json["title"].GetString(),
                                                                               json["subtitle"].GetString(),
                                                                               location,
                                                                               static_cast<float>(json["height_offset"].GetDouble()),
                                                                               indoor,
                                                                               interiorId,
                                                                               json["floor_id"].GetInt(),
                                                                               tags,
                                                                               readableTags,
                                                                               tagIconKey,
                                                                               ExampleApp::Search::EegeoVendorName,
                                                                               userData,
                                                                               Eegeo::Helpers::Time::MillisecondsSinceEpoch());
                    }
                }
                
                EegeoJsonParser::EegeoJsonParser(
                        const SearchResultPoi::SdkModel::ITagIconMapper &tagIconMapper,
                        const EegeoReadableTagMapper& tagReadableNameMapper)
                : m_tagIconMapper(tagIconMapper)
                , m_tagReadableNameMapper(tagReadableNameMapper)
                {

                }

                void EegeoJsonParser::ParseEegeoQueryResults(const std::string& serialized,
                                                                 std::vector<Search::SdkModel::SearchResultModel>& out_results)
                {
                    rapidjson::Document document;
                    
                    if (!document.Parse<0>(serialized.c_str()).HasParseError())
                    {
                        size_t numEntries = document.Size();
                        
                        for(int i = 0; i < numEntries; ++i)
                        {
                            const rapidjson::Value& json = document[i];
                            Search::SdkModel::SearchResultModel result(ParseSearchResultFromJsonObject(json, m_tagIconMapper, m_tagReadableNameMapper));
                            out_results.push_back(result);
                        }
                    }
                }
                
                EegeoSearchResultModel TransformToEegeoSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel)
                {
                    rapidjson::Document json;
                    
                    std::string phone = "";
                    std::string webUrl = "";
                    std::string imageUrl = "";
                    std::string description = "";
                    std::string address = "";
                    
                    if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                    {
                        
                        if(json.HasMember("phone"))
                        {
                            phone = json["phone"].GetString();
                        }
                        
                        if(json.HasMember("web"))
                        {
                            webUrl = json["web"].GetString();
                        }
                        
                        if(json.HasMember("address"))
                        {
                            address = json["address"].GetString();
                        }
                        
                        if(json.HasMember("description"))
                        {
                            description = json["description"].GetString();
                        }
                        
                        if(json.HasMember("image_url"))
                        {
                            imageUrl = json["image_url"].GetString();
                            const size_t lastSlashIndex(imageUrl.rfind("/"));
                            Eegeo_ASSERT(lastSlashIndex != std::string::npos, "The image_url is not well formed: %s.\n",
                                         imageUrl.c_str());
                        }
                    }
                    
                    return EegeoSearchResultModel(phone,
                                                  webUrl,
                                                  address,
                                                  description,
                                                  imageUrl);
                }
                
                bool TryParseImageDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_imageUrl)
                {
                    if(searchResultModel.GetVendor() == ExampleApp::Search::EegeoVendorName)
                    {
                        Search::EegeoPois::SdkModel::EegeoSearchResultModel eegeoResultModel = Search::EegeoPois::SdkModel::TransformToEegeoSearchResult(searchResultModel);
                        
                        out_imageUrl = eegeoResultModel.GetImageUrl();
                        
                        return true;
                    }
                    
                    return false;
                }
            }
        }
    }
}
