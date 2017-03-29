// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "AlbumScreenshotService.h"
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
					: public AlbumScreenshotService
#else
					: public NullScreenshotService
#endif
            {
                iOSScreenshotService(UIView* pView)
#ifdef AUTOMATED_SCREENSHOTS
                : AlbumScreenshotService(pView)
#else
                : NullScreenshotService()
#endif
                {
                }
                
                void OnScreenshotsCompleted()
                {
                }
            };
        }
    }
}
