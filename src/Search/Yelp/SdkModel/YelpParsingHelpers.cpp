// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "YelpParsingHelpers.h"

#include <sstream>
#include <algorithm>
#include <vector>
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include "YelpSearchJsonParser.h"
#include "IYelpCategoryToTagMapper.h"
#include "LatLongAltitude.h"
#include "SearchResultModel.h"
#include "SearchQuery.h"
#include "SearchVendorNames.h"
#include "TimeHelpers.h"
#include "YelpSearchResultModel.h"
#include "SearchVendorNames.h"
#include "ITagIconMapper.h"

using namespace rapidjson;

namespace
{
    struct Result
    {
        std::string placeId;
        std::string address;
        std::string name;

        // This is the result of mapping a yelp category to an app tag
        std::string mappedAppTag;
        std::string uniqueId;
        Eegeo::Space::LatLong location;
        
        Result():location(0.f, 0.f) { }
    };
}

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                
                namespace Helpers
                {
                    ExampleApp::Search::SdkModel::SearchResultModel ParseYelpSearchResultFromJsonObject(const Value& json,
                                                                                                        ExampleApp::Search::Yelp::SdkModel::IYelpCategoryToTagMapper& yelpCategoryMapper,
                                                                                                        const TagSearch::SdkModel::ITagIconMapper& tagIconMapper)
                    {
                        Result entry;
                        
                        entry.address = "";
                        entry.name = "";
                        
                        const Value& name = json["name"];
                        entry.name = name.GetString();
                        
                        std::vector<std::string> humanCategories;
                        std::vector<std::string> allCategories;
                        
                        if(json.HasMember("categories"))
                        {
                            const Value& categoryEntries = json["categories"];
                            const size_t numYelpCategoryEntries(categoryEntries.Size());
                            
                            
                            for(rapidjson::SizeType categoryEntryIndex = 0; categoryEntryIndex < numYelpCategoryEntries; ++categoryEntryIndex)
                            {
                                const Value& categoryEntry = categoryEntries[categoryEntryIndex];
                                const size_t numYelpCategoryEntryStrings(categoryEntry.Size());
                                
                                for(rapidjson::SizeType categoryStringIndex = 0; categoryStringIndex < numYelpCategoryEntryStrings; ++ categoryStringIndex)
                                {
                                    /* Yelp data has category alias pairs; we're only interested in the first
                                     * (more readable) one for generating human-readable categories, e.g.
                                     "categories": [
                                            [
                                                "Mass Media", # friendly / readable
                                                "massmedia"   # skip
                                            ]
                                        ]
                                    */
                                    const bool isReadableYelpCategory = categoryStringIndex % 2 == 0;
                                    if(isReadableYelpCategory)
                                    {
                                        humanCategories.push_back(categoryEntry[categoryStringIndex].GetString());
                                    }
                                    
                                    allCategories.push_back(categoryEntry[categoryStringIndex].GetString());
                                }
                            }
                        }

                        yelpCategoryMapper.TryGetBestMatchingTagForYelpCategories(allCategories, entry.mappedAppTag);
                        
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

                        std::vector<std::string> appTags;
                        appTags.push_back(entry.mappedAppTag);
                        ExampleApp::Search::SdkModel::TagIconKey tagIconKey = tagIconMapper.GetIconKeyForTags(appTags);
                        
                        return ExampleApp::Search::SdkModel::SearchResultModel(ExampleApp::Search::SdkModel::SearchResultModel::CurrentVersion,
                                                                               entry.uniqueId,
                                                                               entry.name,
                                                                               entry.address,
                                                                               entry.location,
                                                                               heightAboveTerrainMetres,
                                                                               interior,
                                                                               building,
                                                                               floor,
                                                                               allCategories,
                                                                               humanCategories,
                                                                               tagIconKey,
                                                                               ExampleApp::Search::YelpVendorName,
                                                                               strbuf.GetString(),
                                                                               Eegeo::Helpers::Time::MillisecondsSinceEpoch());
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
                            Search::Yelp::SdkModel::YelpSearchResultModel yelpResultModel = TransformToYelpSearchResult(searchResultModel);
                            
                            out_imageUrl = yelpResultModel.GetImageUrl();
                            
                            return true;
                        }
                        
                        return false;
                    }
                    
                    bool TryParseReviewDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_ratingImageUrl, int& out_reviewCount)
                    {
                        if(searchResultModel.GetVendor() == ExampleApp::Search::YelpVendorName)
                        {
                            Search::Yelp::SdkModel::YelpSearchResultModel yelpResultModel = TransformToYelpSearchResult(searchResultModel);
                            
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
}