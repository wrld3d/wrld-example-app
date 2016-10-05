// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "IEegeoParser.h"
#include "Types.h"
#include "SearchResultModel.h"
#include "EegeoSearchResultModel.h"
#include "ITagIconMapper.h"
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
                private:
                    std::shared_ptr<const TagSearch::SdkModel::ITagIconMapper> m_tagIconMapper;
                    std::shared_ptr<const EegeoReadableTagMapper> m_tagReadableNameMapper;
                public:
                    EegeoJsonParser(const std::shared_ptr<TagSearch::SdkModel::ITagIconMapper>& tagIconMapper,
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
