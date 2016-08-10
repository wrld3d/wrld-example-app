// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "IEegeoParser.h"
#include "Types.h"
#include "SearchResultModel.h"
#include "EegeoSearchResultModel.h"
#include "ICategoryIconMapper.h"
#include "IPersistentSettingsModel.h"

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
                    const SearchResultPoi::SdkModel::ICategoryIconMapper& m_categoryIconMapper;
                    ExampleApp::PersistentSettings::IPersistentSettingsModel& m_persistentSettings;
                    
                public:
                    EegeoJsonParser(const SearchResultPoi::SdkModel::ICategoryIconMapper& tagIconMapper, PersistentSettings::IPersistentSettingsModel& persistentSettings);
                    void ParseEegeoQueryResults(const std::string& serialized,
                                                std::vector<Search::SdkModel::SearchResultModel>& out_results);
                };

                EegeoSearchResultModel TransformToEegeoSearchResult(const Search::SdkModel::SearchResultModel& searchResultModel);
                
                bool TryParseImageDetails(const Search::SdkModel::SearchResultModel& searchResultModel, std::string& out_imageUrl);
            }
        }
    }
}
