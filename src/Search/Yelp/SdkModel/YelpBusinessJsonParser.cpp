// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "YelpBusinessJsonParser.h"
#include "SearchResultModel.h"
#include "YelpParsingHelpers.h"


#include <document.h>

namespace ExampleApp
{
    namespace Search
    {
        namespace Yelp
        {
            namespace SdkModel
            {
                YelpBusinessJsonParser::YelpBusinessJsonParser(IYelpCategoryToTagMapper& yelpCategoryMapper,
                                                               const TagSearch::SdkModel::ITagIconMapper& tagIconMapper)
                : m_yelpCategoryMapper(yelpCategoryMapper)
                , m_tagIconMapper(tagIconMapper)
                {
                    
                }
                
                bool YelpBusinessJsonParser::TryParse(const std::string& responseString, Search::SdkModel::SearchResultModel& out_result) const
                {
                    
                    rapidjson::Document document;
                    
                    const bool success = !(document.Parse<0>(responseString.c_str()).HasParseError()) && !document.HasMember("error");
                    
                    if (success)
                    {
                        out_result = Helpers::ParseYelpSearchResultFromJsonObject(document, m_yelpCategoryMapper, m_tagIconMapper);
                    }
                    else
                    {
                        Eegeo_TTY("Failed to parse Yelp business result: %s", responseString.c_str());
                        out_result = Search::SdkModel::SearchResultModel();
                    }
                    
                    return success;
                }
            }
        }
    }
}