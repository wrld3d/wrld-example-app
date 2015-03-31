// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Helpers
    {
        namespace ImageHelpers
        {
            std::string GetImageNameForDevice(const std::string& name,
                                              const std::string& ext);

            float GetPixelScale();
        }
    }
}
