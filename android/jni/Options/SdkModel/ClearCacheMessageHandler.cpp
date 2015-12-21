// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ClearCacheMessageHandler.h"
#include "CompletedCacheClearMessage.h"
#include "IHttpCache.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace SdkModel
        {
            ClearCacheMessageHandler::ClearCacheMessageHandler(Eegeo::Helpers::IHttpCache& httpCache,
                                                               ExampleAppMessaging::TMessageBus& messageBus)
            : m_httpCache(httpCache)
            , m_messageBus(messageBus)
            , m_messageHandlerBinding(this, &ClearCacheMessageHandler::OnConfirmedCacheClear)
            {
                m_messageBus.SubscribeNative(m_messageHandlerBinding);
            }
            
            ClearCacheMessageHandler::~ClearCacheMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_messageHandlerBinding);
            }
            
            void ClearCacheMessageHandler::DeleteCacheContents()
            {
            	m_httpCache.ClearCache();
            }
            
            void ClearCacheMessageHandler::OnConfirmedCacheClear(const ClearCacheMessage& message)
            {
                DeleteCacheContents();
                m_messageBus.Publish(CompletedCacheClearMessage());
            }
        }
    }
}
