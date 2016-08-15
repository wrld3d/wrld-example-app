// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "YelpSearchJsonParser.h"
#include "SearchResultModel.h"
#include "YelpParsingHelpers.h"

#include "document.h"


#include <vector>


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
                    rapidjson::Document document;
                    
                    if (!document.Parse<0>(serialized.c_str()).HasParseError() && !document.HasMember("error"))
                    {
                        if(document.HasMember("businesses"))
                        {
                            const rapidjson::Value& entries = document["businesses"];
                            size_t numEntries = entries.Size();
                            
                            for(int i = 0; i < numEntries; ++i)
                            {
                                const rapidjson::Value& json = entries[i];
                                Search::SdkModel::SearchResultModel result(Helpers::ParseYelpSearchResultFromJsonObject(json, m_yelpCategoryMapper));
                                out_results.push_back(result);
                            }
                        }
                    }
                }

            }
        }
    }
}

