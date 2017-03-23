// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "NullScreenshotService.h"
#include "SnapshotScreenshotService.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
            struct iOSScreenshotService
#ifdef AUTOMATED_SCREENSHOTS
					: public SnapshotScreenshotService
#else
					: public NullScreenshotService
#endif
            {
                void OnScreenshotsCompleted()
                {
#ifdef AUTOMATED_SCREENSHOTS
                    terminate();
#endif
                }
            };
        }
    }
}
