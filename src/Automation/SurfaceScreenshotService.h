// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include <functional>
#include <vector>

#include "GlDisplayService.h"
#include "Graphics.h"
#include "ScreenProperties.h"
#include "Types.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
            class SurfaceScreenshotService : public Eegeo::NonCopyable
            {
            public:
                typedef std::function<void(long width, long height, const std::vector<GLubyte>&)> Callback;

                //SurfaceScreenshotService(GlDisplayService& displayService);
                SurfaceScreenshotService(Eegeo::Rendering::ScreenProperties screenProperties);
                ~SurfaceScreenshotService();

                void ExecuteScreenshot();
                void Screenshot(Callback callback);

                void UpdateScreenProperties(const Eegeo::Rendering::ScreenProperties& screenProperties);

            private:
                void ReadPixels(const size_t width, const size_t height);

                Eegeo::Rendering::ScreenProperties m_screenProperties;
                std::vector<GLubyte> m_screenshotBuffer;
                std::vector<Callback> m_callbacks;
                bool m_initialised;
            };
        }
    }
}
