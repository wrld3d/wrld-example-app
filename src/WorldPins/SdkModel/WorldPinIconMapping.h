// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WorldPins.h"
#include "IWorldPinIconMapping.h"
#include "Types.h"
#include <string>
#include <map>

namespace ExampleApp
{
    namespace WorldPins
    {
        namespace SdkModel
        {
            class WorldPinIconMapping : public IWorldPinIconMapping, private Eegeo::NonCopyable
            {
            public:
                WorldPinIconMapping(const std::string& defaultKey, const std::map<std::string, int>& keyToIconIndex);
                
                virtual ~WorldPinIconMapping() { }
                
                virtual int IconIndexForKey(const std::string& key) const;
                
            private:
                const std::string m_defaultKey;
                const std::map<std::string, int> m_keyToIconIndex;
            };
        }
    }
}
