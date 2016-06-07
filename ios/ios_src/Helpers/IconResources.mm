// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "IconResources.h"
#include "ImageHelpers.h"


namespace ExampleApp
{
    namespace Helpers
    {
        namespace IconResources
        {
            std::string GetSmallIconForCategory(const std::string& category)
            {
                return "icon1_" + category;
            }

            std::string GetSmallIconPathForResourceName(const std::string& resource)
            {
                return "icon1_" + resource;
            }

            std::string GetSearchResultIconPathForResourceName(const std::string& resource)
            {
                return "icon1_" + resource;
            }
        }
    }
}
