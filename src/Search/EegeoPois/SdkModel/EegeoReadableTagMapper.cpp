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
                EegeoReadableTagMapper::EegeoReadableTagMapper()
                {
                    m_tagsToReadableNamesMap.insert(std::make_pair("accommodation","Accommodation"));
                    m_tagsToReadableNamesMap.insert(std::make_pair("art_museums","Art & Museum"));
                    m_tagsToReadableNamesMap.insert(std::make_pair("business","Business"));
                    m_tagsToReadableNamesMap.insert(std::make_pair("entertainment","Entertainment"));
                    m_tagsToReadableNamesMap.insert(std::make_pair("food_drink","Food & Drink"));
                    m_tagsToReadableNamesMap.insert(std::make_pair("amenities","General Amenities"));
                    m_tagsToReadableNamesMap.insert(std::make_pair("health","Health"));
                    m_tagsToReadableNamesMap.insert(std::make_pair("shopping","Shopping"));
                    m_tagsToReadableNamesMap.insert(std::make_pair("sports_leisure","Sport & Leisure"));
                    m_tagsToReadableNamesMap.insert(std::make_pair("tourism","Tourist"));
                    m_tagsToReadableNamesMap.insert(std::make_pair("transport","Transport"));
                    m_unknownTagName = "Unknown";
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