// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "IEegeoParser.h"
#include "Types.h"
#include "SearchResultModel.h"
#include "EegeoSearchResultModel.h"
#include "ICategoryIconMapper.h"
#include "EegeoPois.h"

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
                    std::shared_ptr<const SearchResultPoi::SdkModel::ICategoryIconMapper> m_categoryIconMapper;
                    std::shared_ptr<const EegeoReadableTagMapper> m_tagReadableNameMapper;
                public:
                    EegeoJsonParser(const std::shared_ptr<SearchResultPoi::SdkModel::ICategoryIconMapper>& tagIconMapper,
                                    const std::shared_ptr<EegeoReadableTagMapper>& tagReadableNameMapper);
                    
                    void ParseEegeoQueryResults(const std::string& serialized,
                                                std::vector<Search::SdkModel::SearchResultModel>& out_results);
                };

                EegeoSearchResultModel TransformToEegeoSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                
                bool TryParseImageDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_imageUrl);
            }
        }
    }
}
