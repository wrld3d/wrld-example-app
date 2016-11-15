// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "EegeoTagIconMapperFactory.h"
#include "Types.h"

namespace ExampleApp
{
    namespace TagSearch
    {
        namespace SdkModel
        {
            EegeoTagIconMapper* CreateTagIconMapper(const Search::SdkModel::SearchTags& searchTags)
            {
                EegeoTagIconMapper::TTagToTagIconKey mapping = {};

                for(const auto& tag : searchTags.tags)
                {
                    Eegeo_ASSERT(mapping.find(tag.tag) == mapping.end(),
                            "A tag => icon_key mapping already exists for key: %s", tag.tag.c_str());
                    mapping[tag.tag] = tag.iconKey;
                }

                return Eegeo_NEW(EegeoTagIconMapper)(mapping, searchTags.defaultIconKey);
            }
        }
        
    }
}