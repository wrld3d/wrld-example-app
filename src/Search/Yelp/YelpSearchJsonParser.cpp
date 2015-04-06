// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <sstream>
#include <algorithm>
#include <vector>
#include "document.h"
#include "YelpSearchJsonParser.h"
#include "IYelpCategoryMapper.h"
#include "LatLongAltitude.h"
#include "SearchResultModel.h"
#include "SearchQuery.h"
#include "TimeHelpers.h"

using namespace rapidjson;

namespace
{
    struct Result
    {
        std::string placeId;
        std::string phone;
        std::string address;
        std::string webUrl;
        std::string name;
        std::string category;
        std::string vicinity;
        std::string uniqueId;
        std::string imageUrl;
        std::string ratingImageUrl;
        Eegeo::Space::LatLong location;
        
        Result():location(0.f, 0.f) { }
    };
    
    ExampleApp::Search::SdkModel::SearchResultModel ParseYelpSearchResultFromJsonObject(const Value& json,
                                                                                        ExampleApp::Search::Yelp::IYelpCategoryMapper& yelpCategoryMapper)
    {
        Result entry;
        
        entry.phone = "";
        entry.address = "";
        entry.webUrl = "";
        entry.name = "";
        entry.imageUrl = "";
        
        const Value& name = json["name"];
        entry.name = name.GetString();
        
        std::vector<std::string> humanCategories;
        
        if(json.HasMember("categories"))
        {
            const Value& categoryEntries = json["categories"];
            const size_t numYelpCategoryEntries(categoryEntries.Size());
            std::vector<std::string> allCategories;
            
            for(size_t categoryEntryIndex = 0; categoryEntryIndex < numYelpCategoryEntries; ++categoryEntryIndex)
            {
                const Value& categoryEntry = categoryEntries[categoryEntryIndex];
                const size_t numYelpCategoryEntryStrings(categoryEntry.Size());
                
                for(size_t categoryStringIndex = 0; categoryStringIndex < numYelpCategoryEntryStrings; ++ categoryStringIndex)
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
        
        if(json.HasMember("display_phone"))
        {
            entry.phone = json["display_phone"].GetString();
        }
        
        if(json.HasMember("url"))
        {
            entry.webUrl = json["url"].GetString();
        }
        
        if(json.HasMember("image_url"))
        {
            entry.imageUrl = json["image_url"].GetString();
            const size_t lastSlashIndex(entry.imageUrl.rfind("/"));
            Eegeo_ASSERT(lastSlashIndex != std::string::npos, "The image_url is not well formed: %s.\n",
                         entry.imageUrl.c_str());
            entry.imageUrl = entry.imageUrl.substr(0, lastSlashIndex) + "/348s.jpg";
        }
        
        if(json.HasMember("rating"))
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
            
            entry.ratingImageUrl = "stars_" + ratingAsString;
        }
        
        std::vector<std::string> reviews;
        
        if(json.HasMember("snippet_text"))
        {
            reviews.push_back(json["snippet_text"].GetString());
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
                    ss << ", " << displayAddress[displayAddressMembersIndex].GetString();
                }
                
                entry.address = ss.str();
            }
        }
        
        entry.vicinity = entry.address;
        
        const Value& id = json["id"];
        entry.placeId = id.GetString();
        entry.uniqueId = id.GetString();
        
        return ExampleApp::Search::SdkModel::SearchResultModel(ExampleApp::Search::SdkModel::SearchResultModel::CurrentVersion,
                                                               entry.uniqueId,
                                                               entry.name,
                                                               entry.location,
                                                               entry.phone,
                                                               entry.address,
                                                               entry.webUrl,
                                                               entry.category,
                                                               humanCategories,
                                                               entry.vicinity,
                                                               "Yelp",
                                                               entry.imageUrl,
                                                               entry.ratingImageUrl,
                                                               reviews,
                                                               Eegeo::Helpers::Time::MillisecondsSinceEpoch());
    }
    
}

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            YelpSearchJsonParser::YelpSearchJsonParser(IYelpCategoryMapper& yelpCategoryMapper)
            : m_yelpCategoryMapper(yelpCategoryMapper)
            {
                
            }
            
            void YelpSearchJsonParser::ParseSearchResults(const std::string& serialized,
                                                          std::vector<SdkModel::SearchResultModel>& out_results)
            {
                Document document;
                
                if (!document.Parse<0>(serialized.c_str()).HasParseError())
                {
                    if(document.HasMember("businesses"))
                    {
                        const Value& entries = document["businesses"];
                        size_t numEntries = entries.Size();
                        
                        for(int i = 0; i < numEntries; ++i)
                        {
                            const Value& json = entries[i];
                            SdkModel::SearchResultModel result(ParseYelpSearchResultFromJsonObject(json, m_yelpCategoryMapper));
                            out_results.push_back(result);
                        }
                    }
                }
            }
            
            bool TryParseYelpBusinessSearchResult(const std::string& serialized,
                                                  Yelp::IYelpCategoryMapper& yelpCategoryMapper,
                                                  SdkModel::SearchResultModel& out_result)
            {
                Document document;
                
                if (!document.Parse<0>(serialized.c_str()).HasParseError())
                {
                    out_result = ParseYelpSearchResultFromJsonObject(document, yelpCategoryMapper);
                    return true;
                }
                else
                {
                    return false;
                }
            }
        }
    }
}

