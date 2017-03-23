// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "IScreenshotService.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
            enum SnapshotScreenshotServerMessageId
            {
                TakeScreenshotMessageId = 1,
                ScreenshotsCompleteMessageId = 2
            };

            class SnapshotScreenshotService : public ::ExampleApp::Automation::IScreenshotService
            {
            public:
                SnapshotScreenshotService();
                ~SnapshotScreenshotService();

                void screenshot(const std::string& filename);
                void terminate();
                
            private:
                CFMessagePortRef m_port;
            };
        }
    }
}
