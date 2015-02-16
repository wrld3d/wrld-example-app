// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsModelSelectedObserver.h"
#include "IMyPinDetailsDisplayService.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            MyPinDetailsModelSelectedObserver::MyPinDetailsModelSelectedObserver(IMyPinDetailsDisplayService& myPinDetailsDisplayService,
                                                                                 ExampleAppMessaging::TMessageBus& messageBus)
                : m_myPinDetailsDisplayService(myPinDetailsDisplayService)
                , m_messageBus(messageBus)
                , m_handlerBinding(this, &MyPinDetailsModelSelectedObserver::OnMyPinDetailsModelSelectedMessage)
            {
                m_messageBus.SubscribeUi(m_handlerBinding);
            }

            MyPinDetailsModelSelectedObserver::~MyPinDetailsModelSelectedObserver()
            {
                m_messageBus.UnsubscribeUi(m_handlerBinding);
            }

            void MyPinDetailsModelSelectedObserver::OnMyPinDetailsModelSelectedMessage(const MyPinDetailsModelSelectedMessage& message)
            {
                m_myPinDetailsDisplayService.DisplayPinDetails(message.GetModel());
            }
        }
    }
}
