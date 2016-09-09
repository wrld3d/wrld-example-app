// Copyright eeGeo Ltd 2016, All Rights Reserved
#pragma once

#include "EegeoTagIconMapper.h"
#include "SearchTags.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace EegeoPois
        {
            namespace SdkModel
            {
                EegeoTagIconMapper* CreateTagIconMapper(const Search::SdkModel::SearchTags& searchTags);
            }
        }
    }
}