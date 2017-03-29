// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "IScreenshotService.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
            class AlbumScreenshotService : public IScreenshotService
            {
            public:
                AlbumScreenshotService(UIView* pView);
                ~AlbumScreenshotService();

                void screenshot(const std::string& screenshotName);

            private:
                UIImage* CaptureScreenshot();
                void SaveScreenshot(UIImage* screenshot);
                
                UIView* m_pView;
            };
        }
    }
}
