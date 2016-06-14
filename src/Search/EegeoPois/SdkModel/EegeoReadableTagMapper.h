// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Types.h"
#include <string>
#include <map>

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                class EegeoReadableTagMapper : private Eegeo::NonCopyable
                {
                public:
                    EegeoReadableTagMapper();
                    
                    const std::string& GetNameForTag(const std::string& tag) const;
                    
                private:
                    std::map<std::string, const std::string> m_tagsToReadableNamesMap;
                    std::string m_unknownTagName;
                };
            }
        }
    }
}