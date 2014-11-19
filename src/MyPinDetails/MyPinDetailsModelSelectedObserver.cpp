// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinDetailsModelSelectedObserver.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        MyPinDetailsModelSelectedObserver::MyPinDetailsModelSelectedObserver(MyPinDetails::IMyPinDetailsViewModel& myPinDetailsViewModel,
                                                                             ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
        : m_myPinDetailsViewModel(myPinDetailsViewModel)
        , m_nativeToUiMessageBus(nativeToUiMessageBus)
        , m_handlerBinding(this, &MyPinDetailsModelSelectedObserver::HandleReceivedMyPinDetailsModelSelectedMessage)
        {
            m_nativeToUiMessageBus.Subscribe(m_handlerBinding);
        }
        
        MyPinDetailsModelSelectedObserver::~MyPinDetailsModelSelectedObserver()
        {
            m_nativeToUiMessageBus.Unsubscribe(m_handlerBinding);
        }
        
        void MyPinDetailsModelSelectedObserver::HandleReceivedMyPinDetailsModelSelectedMessage(const MyPinDetailsModelSelectedMessage& message)
        {
            if (!m_myPinDetailsViewModel.IsOpen())
            {
                m_myPinDetailsViewModel.Open(message.GetModel());
            }
        }
    }
}
