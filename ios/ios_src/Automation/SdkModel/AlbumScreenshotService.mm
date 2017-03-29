// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include <string>

#include "AlbumScreenshotService.h"
#include "AutomatedScreenshotController.h"
#include "iOSScreenshotService.h"
#include "iOSAutomatedScreenshotController.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
            AlbumScreenshotService::AlbumScreenshotService(UIView* pView)
            : m_pView(pView)
            {
            }

            AlbumScreenshotService::~AlbumScreenshotService()
            {
            }

            void AlbumScreenshotService::screenshot(const std::string&)
            {
                UIImage* screenshot = CaptureScreenshot();
				SaveScreenshot(screenshot);
            }

            UIImage* AlbumScreenshotService::CaptureScreenshot()
			{
                UIGraphicsBeginImageContextWithOptions(m_pView.bounds.size, YES, 0);
                [m_pView drawViewHierarchyInRect:m_pView.frame afterScreenUpdates:YES];
                UIImage *image = UIGraphicsGetImageFromCurrentImageContext();
                UIGraphicsEndImageContext();

				return image;
			}

            void AlbumScreenshotService::SaveScreenshot(UIImage* image)
			{
                UIImageWriteToSavedPhotosAlbum(image, nil, nil, nil);
			}
        }
    }
}
