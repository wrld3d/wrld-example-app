// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#pragma once

#define EEA_SNAPSHOT_PORTNAME "com.eegeo.mobileexampleapp.group.fastlane.port"

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
		}
	}
}
