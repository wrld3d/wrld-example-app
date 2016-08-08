// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "EegeoCategoryIconMapper.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                EegeoCategoryIconMapper::EegeoCategoryIconMapper()
                    : m_defaultCategory("misc")
                {
                    m_tagIconMapping.insert(std::make_pair("aroundme", "aroundme"));
                    m_tagIconMapping.insert(std::make_pair("accommodation", "accommodation"));
                    m_tagIconMapping.insert(std::make_pair("art_museums", "art_museums"));
                    m_tagIconMapping.insert(std::make_pair("business", "business"));
                    m_tagIconMapping.insert(std::make_pair("entertainment", "entertainment"));
                    m_tagIconMapping.insert(std::make_pair("food_drink", "food_drink"));
                    m_tagIconMapping.insert(std::make_pair("amenities", "amenities"));
                    m_tagIconMapping.insert(std::make_pair("health", "health"));
                    m_tagIconMapping.insert(std::make_pair("shopping", "shopping"));
                    m_tagIconMapping.insert(std::make_pair("sports_leisure", "sports_leisure"));
                    m_tagIconMapping.insert(std::make_pair("tourism", "tourism"));
                    m_tagIconMapping.insert(std::make_pair("transport", "transport"));
                    m_tagIconMapping.insert(std::make_pair("meeting_room", "meeting_room"));
                    m_tagIconMapping.insert(std::make_pair("person", "person"));
                    m_tagIconMapping.insert(std::make_pair("department", "department"));
                    m_tagIconMapping.insert(std::make_pair("office", "office"));
                    m_tagIconMapping.insert(std::make_pair("print_station", "print_station"));
                    m_tagIconMapping.insert(std::make_pair("reception", "reception"));
                    m_tagIconMapping.insert(std::make_pair("transition", "transition"));
                    
                }

                EegeoCategoryIconMapper::~EegeoCategoryIconMapper()
                {
                }

                std::string EegeoCategoryIconMapper::GetIconForCategories(const std::vector<std::string>& tags) const
                {
                    for (std::vector<std::string>::const_iterator tag = tags.begin();
                        tag != tags.end();
                        ++tag)
                    {
                        std::map<std::string, std::string>::const_iterator result = m_tagIconMapping.find(*tag);

                        if (result != m_tagIconMapping.end())
                        {
                            return result->second;
                        }
                    }

                    return m_defaultCategory;
                }
            }
        }
    }
}
