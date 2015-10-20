// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinSelectedMessageHandler.h"
#include "ICameraTransitionController.h"
#include "InteriorId.h"

namespace ExampleApp
{
    namespace MyPins
    {
        namespace SdkModel
        {
            MyPinSelectedMessageHandler::MyPinSelectedMessageHandler(CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController,
                    ExampleAppMessaging::TMessageBus& messageBus)
                : m_cameraTransitionController(cameraTransitionController)
                , m_messageBus(messageBus)
                , m_handlerBinding(this, &MyPinSelectedMessageHandler::OnMyPinSelectedMessage)
            {
                m_messageBus.SubscribeNative(m_handlerBinding);
            }

            MyPinSelectedMessageHandler::~MyPinSelectedMessageHandler()
            {
                m_messageBus.UnsubscribeNative(m_handlerBinding);
            }

            void MyPinSelectedMessageHandler::OnMyPinSelectedMessage(const MyPinSelectedMessage& message)
            {
                const float MyPinAltitude = 1500.0f;
                const float MyPinInteriorAltitude = 300.0f;
                if(message.GetInteriorId() == Eegeo::Resources::Interiors::InteriorId::NullId())
                {
                    m_cameraTransitionController.StartTransitionTo(message.GetPinLocation().ToECEF(),
                                                                  MyPinAltitude);
                }
                else
                {
                    m_cameraTransitionController.StartTransitionTo(message.GetPinLocation().ToECEF(),
                                                               MyPinInteriorAltitude,
                                                               message.GetInteriorId(),
                                                               message.GetFloorIndex());
                }
            }
        }
    }
}
