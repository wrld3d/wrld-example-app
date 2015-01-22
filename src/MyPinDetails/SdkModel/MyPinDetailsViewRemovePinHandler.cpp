// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinDetailsViewRemovePinHandler.h"
#include "MyPinsService.h"

namespace ExampleApp
{
    namespace MyPinDetails
    {
        namespace SdkModel
        {
            MyPinDetailsViewRemovePinHandler::MyPinDetailsViewRemovePinHandler(MyPins::SdkModel::IMyPinsService& myPinsService,
                    ExampleAppMessaging::TMessageBus& messageBus)
                : m_myPinsService(myPinsService)
                , m_messageBus(messageBus)
                , m_handler(this, &MyPinDetailsViewRemovePinHandler::OnMyPinCreationViewSavePinMessage)
            {
                m_messageBus.SubscribeNative(m_handler);
            }

            MyPinDetailsViewRemovePinHandler::~MyPinDetailsViewRemovePinHandler()
            {
                m_messageBus.UnsubscribeNative(m_handler);
            }


            void MyPinDetailsViewRemovePinHandler::OnMyPinCreationViewSavePinMessage(const MyPinDetailsViewRemovePinMessage& message)
            {
                m_myPinsService.RemovePinWithId(message.GetMyPinModelId());
            }
        }
    }
}
