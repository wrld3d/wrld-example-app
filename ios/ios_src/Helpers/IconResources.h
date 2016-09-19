// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Helpers
    {
        namespace IconResources
        {
            std::string GetSmallIconForTag(const std::string& tag);

            std::string GetSmallIconPathForResourceName(const std::string& resource);

            std::string GetSearchResultIconPathForResourceName(const std::string& resource);
        }
    }
}
