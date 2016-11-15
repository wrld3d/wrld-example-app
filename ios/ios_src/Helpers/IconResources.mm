// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "IconResources.h"
#include "ImageHelpers.h"


namespace ExampleApp
{
    namespace Helpers
    {
        namespace IconResources
        {
            std::string GetSmallIconForTag(const std::string& tag)
            {
                return "icon1_" + tag;
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
