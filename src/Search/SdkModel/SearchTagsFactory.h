// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include <vector>
#include <string>
#include "Helpers.h"
#include "SearchTags.h"

namespace ExampleApp
{
    namespace Search
    {
        namespace SdkModel
        {
            void PopulateSearchTagsFromFile(Eegeo::Helpers::IFileIO& fileIO, const std::string& fileName, SearchTagRepository& searchTags);
        }
    }
}
