// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <vector>

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace SdkModel
        {
            class ICategoryIconMapper
            {
            public:
                virtual ~ICategoryIconMapper() { }
                
                virtual std::string GetIconForCategories(const std::vector<std::string>& tags) const = 0;
            };
        }
    }
}
