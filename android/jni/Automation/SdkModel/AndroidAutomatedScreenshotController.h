// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "AutomatedScreenshotController.h"
#include "CallbackCollection.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
            class AndroidAutomatedScreenshotController : public Eegeo::NonCopyable
            {
            public:
                AndroidAutomatedScreenshotController(AndroidNativeState &nativeState,
                                                     AutomatedScreenshotController &screenshotController);
                ~AndroidAutomatedScreenshotController();


            private:
                void OnScreenshotsCompleted();

                AndroidNativeState &m_nativeState;
                AutomatedScreenshotController &m_screenshotController;
                Eegeo::Helpers::TCallback0<AndroidAutomatedScreenshotController> m_screenshotsCompletedCallback;

                jclass m_class;
                jobject m_object;
            };
        }
    }
}
