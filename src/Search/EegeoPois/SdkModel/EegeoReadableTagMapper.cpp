// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoReadableTagMapper.h"


namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                EegeoReadableTagMapper::EegeoReadableTagMapper(const std::shared_ptr<Search::SdkModel::SearchTagRepository>& searchTags)
                {
                    for(size_t i = 0; i<searchTags->GetItemCount(); ++i)
                    {
                        const auto& t = searchTags->GetItemAtIndex(i);
                        Eegeo_ASSERT(m_tagsToReadableNamesMap.find(t.GetTag()) == m_tagsToReadableNamesMap.end(),
                            "A mapping already exists for tag %s", t.GetTag().c_str());

                        m_tagsToReadableNamesMap.insert(std::make_pair(t.GetTag(), t.GetReadableTag()));
                    }

                    m_unknownTagName = searchTags->GetDefaultReadableTag();
                }
                
                const std::string& EegeoReadableTagMapper::GetNameForTag(const std::string& tag) const
                {
                    std::map<std::string, const std::string>::const_iterator it = m_tagsToReadableNamesMap.find(tag);
                    if(it != m_tagsToReadableNamesMap.end())
                    {
                        return it->second;
                    }
                    return m_unknownTagName;
                }
            }
        }
    }
}