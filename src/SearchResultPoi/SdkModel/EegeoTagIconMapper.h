// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include "ITagIconMapper.h"
#include "Types.h"
#include "SearchResultModel.h"
#include "SearchTags.h"
#include <memory>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class EegeoTagIconMapper : public SearchResultPoi::SdkModel::ITagIconMapper, private Eegeo::NonCopyable
                {
                public:
                    //TODO: Optimise out values into separate vector
                    typedef std::map<std::string, Search::SdkModel::TagIconKey> TTagToTagIconKey;

                private:
                    TTagToTagIconKey m_tagToTagIconKeyMapping;
                    const std::shared_ptr<Search::SdkModel::SearchTags> m_searchTags;
                    
                public:
                    EegeoTagIconMapper(const std::shared_ptr<Search::SdkModel::SearchTags>& searchTags);

                    ~EegeoTagIconMapper();

                    Search::SdkModel::TagIconKey GetIconKeyForTags(const std::vector<std::string>& tags) const;
                };
            }
        }
    }
}
