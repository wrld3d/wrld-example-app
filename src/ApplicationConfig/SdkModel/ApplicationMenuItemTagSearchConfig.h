// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "ApplicationInteriorTrackingConfig.h"
#include "InteriorId.h"
#include <map>
#include <vector>

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            struct ApplicationMenuItemTagSearchConfig
            {
                std::string name;
                std::string searchTag;
                std::string iconKey;
                bool skipYelp;
                std::string yelpMapping;
                ApplicationMenuItemTagSearchConfig(
                    const std::string& name,
                    const std::string& searchTag,
                    const std::string& iconKey,
                    bool skipYelp,
                    const std::string& yelpMapping)
                : name(name), 
                  searchTag(searchTag),
                  iconKey(iconKey),
                  skipYelp(skipYelp),
                  yelpMapping(yelpMapping)
                {

                }
            };
        }
    }
}
