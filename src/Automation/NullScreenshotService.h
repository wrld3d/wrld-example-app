// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "IScreenshotService.h"

namespace ExampleApp
{
    namespace Automation
    {
        class NullScreenshotService : public IScreenshotService
        {
        public:
            NullScreenshotService();
            ~NullScreenshotService();
            void screenshot(const std::string& filename);
        };
    }
}
