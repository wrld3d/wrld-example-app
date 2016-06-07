// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldPinIconMapping.h"

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            
            WorldPinIconMapping::WorldPinIconMapping(const std::string& defaultKey, const std::map<std::string, int>& keyToIconIndex)
            : m_defaultKey(defaultKey)
            , m_keyToIconIndex(keyToIconIndex)
            {
                Eegeo_ASSERT(!defaultKey.empty(), "defaultKey must not be empty");
                Eegeo_ASSERT((m_keyToIconIndex.find(defaultKey) != m_keyToIconIndex.end()), "keyToIconIndex must provide mapping for default key");
            }
            
            int WorldPinIconMapping::IconIndexForKey(const std::string& key) const
            {
                std::map<std::string, int>::const_iterator iter = m_keyToIconIndex.find(key);
                
                if (iter != m_keyToIconIndex.end())
                {
                    return iter->second;
                }
                else
                {
                    return m_keyToIconIndex.at(m_defaultKey);
                }
            }
        }
    }
}