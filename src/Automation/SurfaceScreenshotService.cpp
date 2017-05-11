// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "GlDisplayService.h"
#include "ScreenProperties.h"
#include "SurfaceScreenshotService.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
            SurfaceScreenshotService::SurfaceScreenshotService(Eegeo::Rendering::ScreenProperties screenProperties)
                : m_screenProperties(screenProperties)
                , m_initialised(false)
            {
            }

            SurfaceScreenshotService::~SurfaceScreenshotService()
            {
            }

            void SurfaceScreenshotService::ExecuteScreenshot()
            {
#ifdef AUTOMATED_SCREENSHOTS
                const bool EnableScreenshots = true;
#else
                const bool EnableScreenshots = false;
#endif
                const size_t width = static_cast<size_t>(m_screenProperties.GetScreenWidth());
                const size_t height = static_cast<size_t>(m_screenProperties.GetScreenHeight());

                if (!m_initialised)
                {
                    ReadPixels(width, height);
                    m_initialised = true;
                }

                if (EnableScreenshots && !m_callbacks.empty())
                {
                    ReadPixels(width, height);
                    for (auto callback : m_callbacks)
                    {
                        callback(width, height, m_screenshotBuffer);
                    }
                    m_callbacks.clear();
                }
            }

            void SurfaceScreenshotService::Screenshot(SurfaceScreenshotService::Callback callback)
            {
                m_callbacks.push_back(callback);
            }

            void SurfaceScreenshotService::UpdateScreenProperties(const Eegeo::Rendering::ScreenProperties& screenProperties)
            {
                m_screenProperties = screenProperties;
            }

            void SurfaceScreenshotService::ReadPixels(const size_t width, const size_t height)
            {
                const size_t bufSize = width * height * 4*sizeof(GLubyte);
                m_screenshotBuffer.reserve(bufSize);
                Eegeo_GL(glReadPixels(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height), GL_RGBA, GL_UNSIGNED_BYTE, &m_screenshotBuffer[0]));
                m_screenshotBuffer.resize(bufSize);
            }
        }
    }
}
