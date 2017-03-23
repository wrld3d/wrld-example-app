// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace Automation
    {
        class IScreenshotService
        {
        public:
            virtual ~IScreenshotService() {}
            virtual void screenshot(const std::string& filename) = 0;
        };
    }
}
