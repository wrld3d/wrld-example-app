// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinsLoadingMessageHandler.h"
#include "IMyPinsService.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            MyPinsLoadingMessageHandler::MyPinsLoadingMessageHandler(const std::shared_ptr<IMyPinsService>& myPinsService,
                                                                     const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus)
            : m_myPinsService(myPinsService)
            , m_messageBus(messageBus)
            , m_handlerBinding(this, &MyPinsLoadingMessageHandler::OnLoadingScreenCompleteMessage)
            {
                m_messageBus->SubscribeNative(m_handlerBinding);
            }
            
            MyPinsLoadingMessageHandler::~MyPinsLoadingMessageHandler()
            {
                m_messageBus->UnsubscribeNative(m_handlerBinding);
            }            
            
            void MyPinsLoadingMessageHandler::OnLoadingScreenCompleteMessage(const LoadingScreenCompleteMessage& message)
            {
                m_myPinsService->LoadAllPinsFromDisk();
            }
        }
    }
}
