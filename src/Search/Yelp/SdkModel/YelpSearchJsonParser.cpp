// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <sstream>
#include <algorithm>
#include <vector>
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include "YelpSearchJsonParser.h"
#include "IYelpCategoryMapper.h"
#include "LatLongAltitude.h"
#include "SearchResultModel.h"
#include "SearchQuery.h"
#include "SearchVendorNames.h"
#include "TimeHelpers.h"
#include "YelpSearchResultModel.h"
#include "SearchVendorNames.h"

using namespace rapidjson;

namespace
{
    struct Result
    {
        std::string placeId;
        std::string address;
        std::string name;
        std::string category;
        std::string uniqueId;
        Eegeo::Space::LatLong location;
        
        Result():location(0.f, 0.f) { }
    };
    
    ExampleApp::Search::SdkModel::SearchResultModel ParseYelpSearchResultFromJsonObject(const Value& json,
                                                                                        ExampleApp::Search::Yelp::SdkModel::IYelpCategoryMapper& yelpCategoryMapper)
    {
        Result entry;
        
        entry.address = "";
        entry.name = "";
        
        const Value& name = json["name"];
        entry.name = name.GetString();
        
        std::vector<std::string> humanCategories;
        
        if(json.HasMember("categories"))
        {
            const Value& categoryEntries = json["categories"];
            const size_t numYelpCategoryEntries(categoryEntries.Size());
            std::vector<std::string> allCategories;
            
            for(rapidjson::SizeType categoryEntryIndex = 0; categoryEntryIndex < numYelpCategoryEntries; ++categoryEntryIndex)
            {
                const Value& categoryEntry = categoryEntries[categoryEntryIndex];
                const size_t numYelpCategoryEntryStrings(categoryEntry.Size());
                
                for(rapidjson::SizeType categoryStringIndex = 0; categoryStringIndex < numYelpCategoryEntryStrings; ++ categoryStringIndex)
                {
                    if(categoryStringIndex%2 == 0)
                    {
                        humanCategories.push_back(categoryEntry[categoryStringIndex].GetString());
                    }
                    
                    allCategories.push_back(categoryEntry[categoryStringIndex].GetString());
                }
            }
            
            yelpCategoryMapper.TryGetBestMatchingApplicationCategoryForYelpCategories(allCategories, entry.category);
        }
    
        if(json.HasMember("location"))
        {
            const Value& locationJson = json["location"];
            
            if(locationJson.HasMember("coordinate"))
            {
                const Value& coordinate = locationJson["coordinate"];
                entry.location = Eegeo::Space::LatLong::FromDegrees(coordinate["latitude"].GetDouble(),
                                                                    coordinate["longitude"].GetDouble());
            }
            
            if(locationJson.HasMember("display_address"))
            {
                const Value& displayAddress = locationJson["display_address"];
                const size_t numDisplayAddressMembers = displayAddress.Size();
                
                std::stringstream ss;
                ss << displayAddress[0u].GetString();
                
                for(size_t displayAddressMembersIndex = 1;
                    displayAddressMembersIndex < numDisplayAddressMembers;
                    ++ displayAddressMembersIndex)
                {
                    ss << ", " << displayAddress[static_cast<unsigned int>(displayAddressMembersIndex)].GetString();
                }
                
                entry.address = ss.str();
            }
        }
        
        const Value& id = json["id"];
        entry.placeId = id.GetString();
        entry.uniqueId = id.GetString();
        
        const bool interior = false;
        const std::string building = "";
        const int floor = 0;
        const float heightAboveTerrainMetres = 0;
        
        rapidjson::StringBuffer strbuf;
        rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
        json.Accept(writer);
        
        return ExampleApp::Search::SdkModel::SearchResultModel(ExampleApp::Search::SdkModel::SearchResultModel::CurrentVersion,
                                                               entry.uniqueId,
                                                               entry.name,
                                                               entry.address,
                                                               entry.location,
                                                               heightAboveTerrainMetres,
                                                               interior,
                                                               building,
                                                               floor,
                                                               entry.category,
                                                               humanCategories,
                                                               ExampleApp::Search::YelpVendorName,
                                                               strbuf.GetString(),
                                                               Eegeo::Helpers::Time::MillisecondsSinceEpoch());
    }
    
}

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                YelpSearchJsonParser::YelpSearchJsonParser(IYelpCategoryMapper& yelpCategoryMapper)
                : m_yelpCategoryMapper(yelpCategoryMapper)
                {
                    
                }
                
                void YelpSearchJsonParser::ParseSearchResults(const std::string& serialized,
                                                              std::vector<Search::SdkModel::SearchResultModel>& out_results)
                {
                    Document document;
                    
                    if (!document.Parse<0>(serialized.c_str()).HasParseError() && !document.HasMember("error"))
                    {
                        if(document.HasMember("businesses"))
                        {
                            const Value& entries = document["businesses"];
                            size_t numEntries = entries.Size();
                            
                            for(int i = 0; i < numEntries; ++i)
                            {
                                const Value& json = entries[i];
                                Search::SdkModel::SearchResultModel result(ParseYelpSearchResultFromJsonObject(json, m_yelpCategoryMapper));
                                out_results.push_back(result);
                            }
                        }
                    }
                }
                
                bool TryParseYelpBusinessSearchResult(const std::string& serialized,
                                                      IYelpCategoryMapper& yelpCategoryMapper,
                                                      Search::SdkModel::SearchResultModel& out_result)
                {
                    Document document;
                    
                    if (!document.Parse<0>(serialized.c_str()).HasParseError() && !document.HasMember("error"))
                    {
                        out_result = ParseYelpSearchResultFromJsonObject(document, yelpCategoryMapper);
                        return true;
                    }
                    else
                    {
                        Eegeo_TTY("Failure to parse business search result: %s", serialized.c_str());
                        return false;
                    }
                }
            
                SdkModel::YelpSearchResultModel TransformToYelpSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel)
                {
                    rapidjson::Document json;
                    
                    std::string phone = "";
                    std::string webUrl = "";
                    std::string imageUrl = "";
                    std::string ratingImageUrl = "";
                    std::vector<std::string> reviews;
                    int reviewCount = 0;
                    

                    
                    if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                    {
                        
                        if(json.HasMember("display_phone"))
                        {
                            phone = json["display_phone"].GetString();
                        }
                        
                        if(json.HasMember("url"))
                        {
                            webUrl = json["url"].GetString();
                        }
                        
                        if(json.HasMember("snippet_text"))
                        {
                            reviews.push_back(json["snippet_text"].GetString());
                        }
                        
                        if(json.HasMember("image_url"))
                        {
                            imageUrl = json["image_url"].GetString();
                            const size_t lastSlashIndex(imageUrl.rfind("/"));
                            Eegeo_ASSERT(lastSlashIndex != std::string::npos, "The image_url is not well formed: %s.\n",
                                         imageUrl.c_str());
                            imageUrl = imageUrl.substr(0, lastSlashIndex) + "/348s.jpg";
                        }
                        if(json.HasMember("rating"))
                        {
                            if(json["rating"].IsString())
                            {
                                ratingImageUrl = json["rating"].GetString();
                            }
                            else
                            {
                                double rating = json["rating"].GetDouble();
                                std::stringstream ss;
                                ss << rating;
                                
                                std::string ratingAsString = ss.str();
                                
                                if (ratingAsString.find('.') == std::string::npos)
                                {
                                    ratingAsString.append(".0");
                                }
                                
                                std::replace(ratingAsString.begin(), ratingAsString.end(), '.', '_');
                                
                                ratingImageUrl = "stars_" + ratingAsString;
                            }
                        }
                        
                        if(json.HasMember("review_count"))
                        {
                            reviewCount = json["review_count"].GetInt();
                        }
                    }
                    
                    return YelpSearchResultModel(phone,
                                                 webUrl,
                                                 searchResultModel.GetSubtitle(),
                                                 imageUrl,
                                                 ratingImageUrl,
                                                 reviews,
                                                 reviewCount);
                }
                
                bool TryParseImageDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_imageUrl)
                {
                    if(searchResultModel.GetVendor() == ExampleApp::Search::YelpVendorName)
                    {
                        Search::Yelp::SdkModel::YelpSearchResultModel yelpResultModel = Search::Yelp::SdkModel::TransformToYelpSearchResult(searchResultModel);
                        
                        out_imageUrl = yelpResultModel.GetImageUrl();
                        
                        return true;
                    }
                    
                    return false;
                }
                
                bool TryParseReviewDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_ratingImageUrl, int& out_reviewCount)
                {
                    if(searchResultModel.GetVendor() == ExampleApp::Search::YelpVendorName)
                    {
                        Search::Yelp::SdkModel::YelpSearchResultModel yelpResultModel = Search::Yelp::SdkModel::TransformToYelpSearchResult(searchResultModel);
                        
                        out_ratingImageUrl = yelpResultModel.GetRatingImageUrl();
                        out_reviewCount = yelpResultModel.GetReviewCount();
                        
                        return true;
                    }
                    
                    return false;
                }
            }
        }
    }
}

