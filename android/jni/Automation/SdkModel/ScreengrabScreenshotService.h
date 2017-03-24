// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <jni.h>
#include <string>

#include "AndroidNativeState.h"
#include "IScreenshotService.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
            class ScreengrabScreenshotService : public IScreenshotService
            {
            public:
                ScreengrabScreenshotService(AndroidNativeState& androidNativeState);
                ~ScreengrabScreenshotService();
                void screenshot(const std::string& filename);

            private:
                AndroidNativeState& m_nativeState;
                jclass m_class;
            };
        }
    }
}
