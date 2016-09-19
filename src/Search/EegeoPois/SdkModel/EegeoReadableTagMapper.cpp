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
                EegeoReadableTagMapper::EegeoReadableTagMapper(const Search::SdkModel::SearchTags& searchTags)
                {
                    for(const auto& i : searchTags.tags)
                    {
                        Eegeo_ASSERT(m_tagsToReadableNamesMap.find(i.tag) == m_tagsToReadableNamesMap.end(),
                            "A mapping already exists for tag %s", i.tag.c_str());

                        m_tagsToReadableNamesMap.insert(std::make_pair(i.tag, i.readableTag));
                    }

                    m_unknownTagName = searchTags.defaultReadableTag;
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