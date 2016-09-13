// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "EegeoTagIconMapper.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                EegeoTagIconMapper::EegeoTagIconMapper(const std::shared_ptr<Search::SdkModel::SearchTags>& searchTags)
                    : m_searchTags(searchTags)
                {
                    for(const auto& tag : searchTags->tags)
                    {
                        Eegeo_ASSERT(m_tagToTagIconKeyMapping.find(tag.tag) == m_tagToTagIconKeyMapping.end(),
                                     "A tag => icon_key mapping already exists for key: %s", tag.tag.c_str());
                        m_tagToTagIconKeyMapping[tag.tag] = tag.iconKey;
                    }
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

                    return m_searchTags->defaultIconKey;
                }
            }
        }
    }
}
