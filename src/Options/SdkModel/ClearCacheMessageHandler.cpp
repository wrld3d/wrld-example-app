// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ClearCacheMessageHandler.h"
#include "CacheClearBackgroundTask.h"
#include "IWorkPool.h"
#include "IHttpCache.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace SdkModel
        {
            ClearCacheMessageHandler::ClearCacheMessageHandler(const std::shared_ptr<Eegeo::Helpers::IHttpCache>& httpCache,
                                                               const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                               const std::shared_ptr<Eegeo::Concurrency::Tasks::IWorkPool>& workPool)
            : m_httpCache(httpCache)
            , m_messageBus(messageBus)
            , m_workPool(workPool)
            , m_messageHandlerBinding(this, &ClearCacheMessageHandler::OnConfirmedCacheClear)
            {
                m_messageBus->SubscribeNative(m_messageHandlerBinding);
            }
            
            ClearCacheMessageHandler::~ClearCacheMessageHandler()
            {
                m_messageBus->UnsubscribeNative(m_messageHandlerBinding);
            }
            
            void ClearCacheMessageHandler::DeleteCacheContents()
            {
                CacheClearBackgroundTask* pTask(Eegeo_NEW(CacheClearBackgroundTask)(*m_httpCache, *m_messageBus));
                m_workPool->QueueWork(pTask);
            }
            
            void ClearCacheMessageHandler::OnConfirmedCacheClear(const ClearCacheMessage& message)
            {
                DeleteCacheContents();
            }
        }
    }
}
