// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "iOSScreenshotService.h"
#include "AutomatedScreenshotController.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
            class iOSAutomatedScreenshotController : public Eegeo::NonCopyable
            {
            public:
                iOSAutomatedScreenshotController(iOSScreenshotService& screenshotService, AutomatedScreenshotController &screenshotController);
                ~iOSAutomatedScreenshotController();


            private:
                void OnScreenshotsCompleted();

                AutomatedScreenshotController &m_screenshotController;
                Eegeo::Helpers::TCallback0<iOSAutomatedScreenshotController> m_screenshotsCompletedCallback;

                iOSScreenshotService& m_screenshotService;
            };
        }
    }
}
