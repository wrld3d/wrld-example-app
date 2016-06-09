// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoJsonParser.h"
#include "SearchVendorNames.h"
#include "TimeHelpers.h"
#include "InteriorId.h"

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
                                tags.push_back(str.substr(previous_start + 1, i - previous_start));
                                previous_start = i;
                            }
                        }

                        if (previous_start != str.length() - 1)
                        {
                            tags.push_back(str.substr(previous_start + 1));
                        }

                        return tags;
                    }

                    Search::SdkModel::SearchResultModel ParseSearchResultFromJsonObject(const rapidjson::Value& json, const SearchResultPoi::SdkModel::ICategoryIconMapper& tagIconMapper)
                    {
                        Eegeo::Space::LatLong location = Eegeo::Space::LatLong::FromDegrees(json["lat"].GetDouble(),
                                                                                            json["lon"].GetDouble());
                        
                        std::stringstream idStream;
                        idStream << json["id"].GetInt();
                        
                        bool indoor = json["indoor"].GetBool();
                        Eegeo::Resources::Interiors::InteriorId interiorId(json["indoor_id"].GetString());
                        
                        std::vector<std::string> tags = SplitIntoTags(json["tags"].GetString(), ' ');

                        std::string category = tagIconMapper.GetIconForCategories(tags);
                        
                        std::string userData = "";
                        
                        if (json.HasMember("user_data"))
                        {
                            if (json["user_data"].HasMember("subcategory") && json["user_data"]["subcategory"].IsString())
                            {
                                category = json["user_data"]["subcategory"].GetString();
                            }
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
                                                                               category,
                                                                               tags,
                                                                               ExampleApp::Search::EegeoVendorName,
                                                                               userData,
                                                                               Eegeo::Helpers::Time::MillisecondsSinceEpoch());
                    }
                }
                
                EegeoJsonParser::EegeoJsonParser(const SearchResultPoi::SdkModel::ICategoryIconMapper &categoryIconMapper)
                :m_categoryIconMapper(categoryIconMapper)
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
                            Search::SdkModel::SearchResultModel result(ParseSearchResultFromJsonObject(json, m_categoryIconMapper));
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
