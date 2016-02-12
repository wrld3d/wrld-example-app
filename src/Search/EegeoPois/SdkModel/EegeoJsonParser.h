// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "IEegeoParser.h"
#include "Types.h"
#include "SearchResultModel.h"
#include "EegeoSearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class EegeoJsonParser : public IEegeoParser, private Eegeo::NonCopyable
                {
                public:
                    
                    void ParseEegeoQueryResults(const std::string& serialized,
                                                std::vector<Search::SdkModel::SearchResultModel>& out_results);
                };

                EegeoSearchResultModel TransformToEegeoSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                
                bool TryParseImageDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_imageUrl);
            }
        }
    }
}
