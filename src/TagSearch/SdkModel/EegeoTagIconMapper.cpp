// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "EegeoTagIconMapper.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace SdkModel
        {
            EegeoTagIconMapper::EegeoTagIconMapper(
                    const TTagToTagIconKey& tagToTagIconKeyMapping,
                    const Search::SdkModel::TagIconKey& defaultIconKey)
                : m_tagToTagIconKeyMapping(tagToTagIconKeyMapping)
                , m_defaultIconKey(defaultIconKey)
            {

            }

            EegeoTagIconMapper::~EegeoTagIconMapper()
            {
            }

            ExampleApp::Search::SdkModel::TagIconKey EegeoTagIconMapper::GetIconKeyForTags(const std::vector<std::string>& tags) const
            {
                for (std::vector<std::string>::const_iterator tag = tags.begin();
                    tag != tags.end();
                    ++tag)
                {
                    std::map<std::string, std::string>::const_iterator result = m_tagToTagIconKeyMapping.find(*tag);

                    if (result != m_tagToTagIconKeyMapping.end())
                    {
                        return result->second;
                    }
                }

                return m_defaultIconKey;
            }
        }
    }
}
