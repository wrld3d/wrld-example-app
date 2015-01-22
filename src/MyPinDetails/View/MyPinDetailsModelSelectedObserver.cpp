// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsModelSelectedObserver.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace View
        {
            MyPinDetailsModelSelectedObserver::MyPinDetailsModelSelectedObserver(IMyPinDetailsViewModel& myPinDetailsViewModel,
                    ExampleAppMessaging::TMessageBus& messageBus)
                : m_myPinDetailsViewModel(myPinDetailsViewModel)
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
                if (!m_myPinDetailsViewModel.IsOpen())
                {
                    m_myPinDetailsViewModel.Open(message.GetModel());
                }
            }
        }
    }
}
