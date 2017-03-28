// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <jni.h>

#include "AndroidNativeState.h"
#include "IScreenshotService.h"
#include "SurfaceScreenshotService.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
            class AlbumScreenshotService : public Eegeo::NonCopyable, public IScreenshotService
            {
            public:
                AlbumScreenshotService(AndroidNativeState& nativeState, SurfaceScreenshotService& surfaceScreenshotService);
                ~AlbumScreenshotService();

                void screenshot(const std::string& screenshotName);
                void AsyncSurfaceScreenshot(jobject compositor);

            private:
                AndroidNativeState& m_nativeState;
                SurfaceScreenshotService& m_surfaceScreenshotService;
                jclass m_screenshotCompositorClass;
                jclass m_class;
                jobject m_object;
            };
        }
    }
}
