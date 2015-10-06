// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ExampleSearchJsonParser.h"
#include "SearchVendorNames.h"
#include "document.h"
#include "writer.h"
#include "stringbuffer.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace Example
        {
            namespace SdkModel
            {
                ExampleSearchResultModel TransformToExampleSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel)
                {
                    rapidjson::Document json;
                    
                    std::string imageUrl = "";
                    
                    if (!json.Parse<0>(searchResultModel.GetJsonData().c_str()).HasParseError())
                    {
                        if(json.HasMember("imageUrl"))
                        {
                            imageUrl = json["imageUrl"].GetString();
                        }
                    }
                    
                    return ExampleSearchResultModel(imageUrl);
                }
                
                bool TryParseImageDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_imageUrl)
                {
                    const bool canUseVendor = (searchResultModel.GetVendor() == ExampleTourVendorName);
                    
                    if(canUseVendor)
                    {
                        ExampleSearchResultModel ExampleResult = TransformToExampleSearchResult(searchResultModel);
                        
                        out_imageUrl = ExampleResult.GetImageUrl();
                        return true;
                    }
                    return false;
                }
            }
        }
    }
}