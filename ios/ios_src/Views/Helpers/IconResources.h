// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Helpers
    {
        namespace IconResources
        {
            std::string GetCategoryMatch(std::string category);
            
            std::string GetSmallIconForCategory(const std::string& category);
            
            std::string GetSmallIconPathForResourceName(const std::string& resource);
            
            std::string GetSearchResultIconPathForResourceName(const std::string& resource);
        }
    }
}
