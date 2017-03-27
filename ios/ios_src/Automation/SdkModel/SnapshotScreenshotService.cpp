// Copyright eeGeo Ltd (2012-2017), All Rights Reserved

#include <CoreFoundation/CFMessagePort.h>
#include "SnapshotMessageConstants.h"
#include "SnapshotScreenshotService.h"

namespace ExampleApp
{
    namespace Automation
    {
        namespace SdkModel
        {
            namespace
            {
                const CFTimeInterval MessageRxTimeout = 1000;
            }
            
            SnapshotScreenshotService::SnapshotScreenshotService()
                : m_port(CFMessagePortCreateRemote(kCFAllocatorDefault, CFSTR(EEA_SNAPSHOT_PORTNAME)))
            {
            }

            SnapshotScreenshotService::~SnapshotScreenshotService()
            {
                CFRelease(m_port);
            }

            void SnapshotScreenshotService::screenshot(const std::string& filename)
			{
				CFDataRef messageData(CFDataCreate(kCFAllocatorDefault, (const UInt8*) filename.data(), filename.size()));
                CFMessagePortSendRequest(m_port, TakeScreenshotMessageId, messageData, MessageRxTimeout, MessageRxTimeout, NULL, NULL);
				CFRelease(messageData);
			}
            
            void SnapshotScreenshotService::terminate()
            {
                CFMessagePortSendRequest(m_port, ScreenshotsCompleteMessageId, NULL, MessageRxTimeout, MessageRxTimeout, NULL, NULL);
            }
        }
    }
}
