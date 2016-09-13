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
                EegeoTagIconMapper::EegeoTagIconMapper(const std::shared_ptr<Search::SdkModel::SearchTagRepository>& searchTags)
                    : m_searchTags(searchTags)
                {
                    for(size_t i = 0; i<searchTags->GetItemCount(); ++i)
                    {
                        const auto& tag = searchTags->GetItemAtIndex(i);
                        Eegeo_ASSERT(m_tagToTagIconKeyMapping.find(tag.GetTag()) == m_tagToTagIconKeyMapping.end(),
                                     "A tag => icon_key mapping already exists for key: %s", tag.GetTag().c_str());
                        m_tagToTagIconKeyMapping[tag.GetTag()] = tag.GetIconKey();
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

                    return m_searchTags->GetDefaultIconKey();
                }
            }
        }
    }
}
