// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "ScreengrabScreenshotService.h"
#include "NullScreenshotService.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
#ifdef AUTOMATED_SCREENSHOTS
            struct AndroidScreenshotService : public ScreengrabScreenshotService
            {
                AndroidScreenshotService(AndroidNativeState& nativeState)
                    : ScreengrabScreenshotService(nativeState)
                {
                }
            };
#else
            struct AndroidScreenshotService : public NullScreenshotService
            {
                AndroidScreenshotService(AndroidNativeState&)
                {
                }
            };
#endif
        }
    }
}
