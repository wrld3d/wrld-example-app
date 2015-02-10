// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CacheClearBackgroundTask.h"
#include "CompletedCacheClearMessage.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace SdkModel
        {
            void CacheClearBackgroundTask::DoWork()
            {
                m_iOSHttpCache.ClearCache();
            }
            
            void CacheClearBackgroundTask::DoFinalizeOnMainThread()
            {
                m_messageBus.Publish(CompletedCacheClearMessage());
            }
        }
    }
}
