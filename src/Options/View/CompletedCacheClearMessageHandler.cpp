// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "CompletedCacheClearMessageHandler.h"
#include "IOptionsViewModel.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            CompletedCacheClearMessageHandler::CompletedCacheClearMessageHandler(IOptionsViewModel& optionsViewModel,
                                                                                 ExampleAppMessaging::TMessageBus& messageBus)
            : m_optionsViewModel(optionsViewModel)
            , m_messageBus(messageBus)
            , m_messageHandlerBinding(this, &CompletedCacheClearMessageHandler::OnCompletedCacheClear)
            {
                m_messageBus.SubscribeUi(m_messageHandlerBinding);
            }
            
            CompletedCacheClearMessageHandler::~CompletedCacheClearMessageHandler()
            {
                m_messageBus.UnsubscribeUi(m_messageHandlerBinding);
            }
            
            void CompletedCacheClearMessageHandler::OnCompletedCacheClear(const CompletedCacheClearMessage& message)
            {
                m_optionsViewModel.EndCacheClearCeremony();
            }
        }
    }
}
