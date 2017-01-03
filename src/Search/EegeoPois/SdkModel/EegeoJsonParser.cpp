// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoJsonParser.h"
#include "SearchVendorNames.h"
#include "TimeHelpers.h"
#include "InteriorId.h"
#include "EegeoReadableTagMapper.h"
#include "ITagIconMapper.h"
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
                                                                                        const TagSearch::SdkModel::ITagIconMapper& tagIconMapper,
                                                                                        const EegeoReadableTagMapper& tagNameMapper)
                    {
                        std::string title = "";
                        std::string subtitle = "";
                        double lat = 0.0;
                        double lon = 0.0;
                        float heightOffset = 0.f;
                        int floorId = 0;
                        int id = 0;
                        bool indoor = false;
                        std::string indoorId = "";
                        std::string tags = "";
                        
                        const std::string titleName = "title";
                        const std::string subtitleName = "subtitle";
                        const std::string heightOffsetName = "height_offset";
                        const std::string floorIdName = "floor_id";
                        const std::string latName = "lat";
                        const std::string lonName = "lon";
                        const std::string idName = "id";
                        const std::string indoorName = "indoor";
                        const std::string indoorIdName = "indoor_id";
                        const std::string tagsName = "tags";
                        const std::string userDataName = "user_data";
                        
                        if(json.HasMember(titleName.c_str()) && json[titleName.c_str()].IsString())
                        {
                            title = json[titleName.c_str()].GetString();
                        }
                        
                        if(json.HasMember(subtitleName.c_str()) && json[subtitleName.c_str()].IsString())
                        {
                            subtitle = json[subtitleName.c_str()].GetString();
                        }
                        
                        if(json.HasMember(heightOffsetName.c_str()) && json[heightOffsetName.c_str()].IsDouble())
                        {
                            heightOffset = static_cast<float>(json[heightOffsetName.c_str()].GetDouble());
                        }
                        
                        if(json.HasMember(floorIdName.c_str()) && json[floorIdName.c_str()].IsInt())
                        {
                            floorId = json[floorIdName.c_str()].GetInt();
                        }
                        
                        if(json.HasMember(latName.c_str()) && json[latName.c_str()].IsDouble())
                        {
                            lat = json[latName.c_str()].GetDouble();
                        }
                        
                        if(json.HasMember(lonName.c_str()) && json[lonName.c_str()].IsDouble())
                        {
                            lon = json[lonName.c_str()].GetDouble();
                        }
                        
                        if(json.HasMember(idName.c_str()) && json[idName.c_str()].IsInt())
                        {
                            id = json[idName.c_str()].GetInt();
                        }
                        
                        if(json.HasMember(indoorName.c_str()) && json[indoorName.c_str()].IsBool())
                        {
                            indoor = json[indoorName.c_str()].GetBool();
                        }
                        
                        if(json.HasMember(indoorIdName.c_str()) && json[indoorIdName.c_str()].IsString())
                        {
                            indoorId = json[indoorIdName.c_str()].GetString();
                        }
                        
                        if(json.HasMember(tagsName.c_str()) && json[tagsName.c_str()].IsString())
                        {
                            tags = json[tagsName.c_str()].GetString();
                        }
                        
                        Eegeo::Space::LatLong location = Eegeo::Space::LatLong::FromDegrees(lat, lon);
                        
                        std::stringstream idStream;
                        idStream << id;
                        
                        Eegeo::Resources::Interiors::InteriorId interiorId(indoorId);
                        
                        std::vector<std::string> tagSet = SplitIntoTags(tags, ' ');
                        std::vector<std::string> readableTags = GetNamesForTags(tagSet, tagNameMapper);

                        const Search::SdkModel::TagIconKey& tagIconKey = tagIconMapper.GetIconKeyForTags(tagSet);
                        
                        std::string userData = "";
                        
                        if (json.HasMember(userDataName.c_str()) && json[userDataName.c_str()].IsObject())
                        {
                            rapidjson::StringBuffer strbuf;
                            rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
                            json[userDataName.c_str()].Accept(writer);
                            userData = strbuf.GetString();
                        }
                        
                        return ExampleApp::Search::SdkModel::SearchResultModel(ExampleApp::Search::SdkModel::SearchResultModel::CurrentVersion,
                                                                               idStream.str(),
                                                                               title,
                                                                               subtitle,
                                                                               location,
                                                                               heightOffset,
                                                                               indoor,
                                                                               interiorId,
                                                                               floorId,
                                                                               tagSet,
                                                                               readableTags,
                                                                               tagIconKey,
                                                                               ExampleApp::Search::EegeoVendorName,
                                                                               userData,
                                                                               Eegeo::Helpers::Time::MillisecondsSinceEpoch());
                    }
                }
                
                EegeoJsonParser::EegeoJsonParser(
                        const TagSearch::SdkModel::ITagIconMapper &tagIconMapper,
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
                    std::string facebookUrl = "";
                    std::string twitterUrl = "";
                    std::string email = "";
                    std::string customViewUrl = "";
                    int customViewHeight = -1;
                    
                    const std::string phoneName = "phone";
                    const std::string webName = "web";
                    const std::string addressName = "address";
                    const std::string descriptionName = "description";
                    const std::string imageName = "image_url";
                    const std::string facebookName = "facebook";
                    const std::string twitterName = "twitter";
                    const std::string emailName = "email";
                    const std::string customViewUrlName = "custom_view";
                    const std::string customViewHeightName = "custom_view_height";
                    
                    if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                    {
                        if(json.HasMember(phoneName.c_str()) && json[phoneName.c_str()].IsString())
                        {
                            phone = json[phoneName.c_str()].GetString();
                        }
                        
                        if(json.HasMember(webName.c_str()) && json[webName.c_str()].IsString())
                        {
                            webUrl = json[webName.c_str()].GetString();
                        }
                        
                        if(json.HasMember(addressName.c_str()) && json[addressName.c_str()].IsString())
                        {
                            address = json[addressName.c_str()].GetString();
                        }
                        
                        if(json.HasMember(descriptionName.c_str()) && json[descriptionName.c_str()].IsString())
                        {
                            description = json[descriptionName.c_str()].GetString();
                        }
                        
                        if(json.HasMember(imageName.c_str()) && json[imageName.c_str()].IsString())
                        {
                            imageUrl = json[imageName.c_str()].GetString();
                        }
                        
                        if(json.HasMember(facebookName.c_str()) && json[facebookName.c_str()].IsString())
                        {
                            facebookUrl = json[facebookName.c_str()].GetString();
                        }
                        
                        if(json.HasMember(twitterName.c_str()) && json[twitterName.c_str()].IsString())
                        {
                            twitterUrl = json[twitterName.c_str()].GetString();
                        }
                        
                        if(json.HasMember(emailName.c_str()) && json[emailName.c_str()].IsString())
                        {
                            email = json[emailName.c_str()].GetString();
                        }
                        
                        if(json.HasMember(customViewUrlName.c_str()) && json[customViewUrlName.c_str()].IsString())
                        {
                            customViewUrl = json[customViewUrlName.c_str()].GetString();
                        }
                        
                        if(json.HasMember(customViewHeightName.c_str()) && json[customViewHeightName.c_str()].IsInt())
                        {
                            customViewHeight = json[customViewHeightName.c_str()].GetInt();
                        }
                    }
                    
                    return EegeoSearchResultModel(phone,
                                                  webUrl,
                                                  address,
                                                  description,
                                                  imageUrl,
                                                  facebookUrl,
                                                  twitterUrl,
                                                  email,
                                                  customViewUrl,
                                                  customViewHeight);
                }
                
                bool TryParseImageDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_imageUrl)
                {
                    if(searchResultModel.GetVendor() == ExampleApp::Search::EegeoVendorName)
                    {
                        Search::EegeoPois::SdkModel::EegeoSearchResultModel eegeoResultModel = Search::EegeoPois::SdkModel::TransformToEegeoSearchResult(searchResultModel);
                        const size_t lastSlashIndex(eegeoResultModel.GetImageUrl().rfind("/"));

                        if (lastSlashIndex != std::string::npos)
                        {
                            out_imageUrl = eegeoResultModel.GetImageUrl();

                            return true;
                        }
                    }
                    
                    return false;
                }
            }
        }
    }
}
