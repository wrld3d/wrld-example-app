// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinSelectedMessageHandler.h"
#include "ICameraTransitionController.h"

namespace ExampleApp
{
    namespace MyPins
    {
        MyPinSelectedMessageHandler::MyPinSelectedMessageHandler(CameraTransitions::ICameraTransitionController& cameraTransitionController,
                                                                 ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
        : m_cameraTransitionController(cameraTransitionController)
        , m_uiToNativeMessageBus(uiToNativeMessageBus)
        , m_handlerBinding(this, &MyPinSelectedMessageHandler::HandleReceivedMyPinSelectedMessage)
        {
            m_uiToNativeMessageBus.Subscribe(m_handlerBinding);
        }
        
        MyPinSelectedMessageHandler::~MyPinSelectedMessageHandler()
        {
            m_uiToNativeMessageBus.Unsubscribe(m_handlerBinding);
        }
        
        void MyPinSelectedMessageHandler::HandleReceivedMyPinSelectedMessage(const MyPinSelectedMessage& message)
        {
            const float MyPinAltitude = 1500.0f;
            m_cameraTransitionController.StartTransitionTo(message.Model().GetLatLong().ToECEF(), MyPinAltitude);
        }
    }
}
