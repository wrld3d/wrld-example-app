// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include "iOSScreenshotService.h"
#include "iOSAutomatedScreenshotController.h"
#include "AutomatedScreenshotController.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
            iOSAutomatedScreenshotController::iOSAutomatedScreenshotController(iOSScreenshotService& screenshotService, AutomatedScreenshotController& screenshotController)
            : m_screenshotController(screenshotController)
            , m_screenshotsCompletedCallback(this, &iOSAutomatedScreenshotController::OnScreenshotsCompleted)
            , m_screenshotService(screenshotService)
            {
                m_screenshotController.InsertCompletedScreenshotsCallback(m_screenshotsCompletedCallback);
            }

            iOSAutomatedScreenshotController::~iOSAutomatedScreenshotController()
            {
                m_screenshotController.RemoveCompletedScreenshotsCallback(m_screenshotsCompletedCallback);
            }

            void iOSAutomatedScreenshotController::OnScreenshotsCompleted()
            {
                m_screenshotService.OnScreenshotsCompleted();
            }
        }
    }
}
