// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "AlbumScreenshotService.h"
#include "NullScreenshotService.h"
#include "ScreengrabScreenshotService.h"
#include "SurfaceScreenshotService.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
#ifdef AUTOMATED_SCREENSHOTS
            struct AndroidScreenshotService : public AlbumScreenshotService
            {
                AndroidScreenshotService(AndroidNativeState& nativeState, SurfaceScreenshotService& surfaceScreenshotService)
                    : AlbumScreenshotService(nativeState, surfaceScreenshotService)
                {
                }
            };
#else
            struct AndroidScreenshotService : public NullScreenshotService
            {
                AndroidScreenshotService(AndroidNativeState&, SurfaceScreenshotService&)
                {
                }
            };
#endif
        }
    }
}
