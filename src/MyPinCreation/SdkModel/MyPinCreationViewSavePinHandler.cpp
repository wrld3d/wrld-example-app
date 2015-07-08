// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "MyPinCreationViewSavePinHandler.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
        namespace SdkModel
        {
            MyPinCreationViewSavePinHandler::MyPinCreationViewSavePinHandler(IMyPinCreationModel& myPinCreationModel,
                    ExampleAppMessaging::TMessageBus& messageBus)
                : m_myPinCreationModel(myPinCreationModel)
                , m_messageBus(messageBus)
                , m_handler(this, &MyPinCreationViewSavePinHandler::OnMyPinCreationViewSavePinMessageMessage)
            {
                m_messageBus.SubscribeNative(m_handler);
            }

            MyPinCreationViewSavePinHandler::~MyPinCreationViewSavePinHandler()
            {
                m_messageBus.UnsubscribeNative(m_handler);
            }

            void MyPinCreationViewSavePinHandler::OnMyPinCreationViewSavePinMessageMessage(const MyPinCreationViewSavePinMessage& message)
            {
                m_myPinCreationModel.SavePoi(message.GetTitle(),
                                             message.GetDescription(),
                                             "",
                                             0,
                                             message.GetImageData(),
                                             message.GetImageSize(),
                                             message.GetShouldShare());
            }
        }
    }
}
