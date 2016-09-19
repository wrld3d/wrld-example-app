// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <vector>
#include <string>
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            struct SearchTag
            {
                std::string tag;
                std::string readableTag;
                TagIconKey iconKey;

                SearchTag(const std::string& tag,
                          const std::string& readableTag,
                          const TagIconKey& iconKey)

                : tag(tag), readableTag(readableTag), iconKey(iconKey)
                {

                }

            };

            struct SearchTags
            {
                std::vector<SearchTag> tags;
                std::string defaultReadableTag;
                TagIconKey defaultIconKey;
            };
        }
    }
}
