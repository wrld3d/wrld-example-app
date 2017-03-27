// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#include "IScreenshotService.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
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
