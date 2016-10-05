// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include "ITagIconMapper.h"
#include "Types.h"
#include "SearchResultModel.h"
#include "SearchTags.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace SdkModel
        {
            class EegeoTagIconMapper : public ITagIconMapper, private Eegeo::NonCopyable
            {
            public:
                //TODO: Optimise out values into separate vector
                typedef std::map<std::string, Search::SdkModel::TagIconKey> TTagToTagIconKey;

            private:
                TTagToTagIconKey m_tagToTagIconKeyMapping;
                Search::SdkModel::TagIconKey m_defaultIconKey;

            public:
                EegeoTagIconMapper(const std::shared_ptr<Search::SdkModel::SearchTagRepository>& searchTags);

                ~EegeoTagIconMapper();

                Search::SdkModel::TagIconKey GetIconKeyForTags(const std::vector<std::string>& tags) const;
            };
        }
    }
}
