// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationViewSavePinHandler.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
		MyPinCreationViewSavePinHandler::MyPinCreationViewSavePinHandler(IMyPinCreationModel& myPinCreationModel,
										ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
		: m_myPinCreationModel(myPinCreationModel)
		, m_uiToNativeMessageBus(uiToNativeMessageBus)
		, m_handler(this, &MyPinCreationViewSavePinHandler::OnMyPinCreationViewSavePinMessageReceived)
		{
			m_uiToNativeMessageBus.Subscribe(m_handler);
		}

		MyPinCreationViewSavePinHandler::~MyPinCreationViewSavePinHandler()
		{
			m_uiToNativeMessageBus.Unsubscribe(m_handler);
		}

		void MyPinCreationViewSavePinHandler::OnMyPinCreationViewSavePinMessageReceived(const MyPinCreationViewSavePinMessage& message)
		{
			m_myPinCreationModel.SavePoi(message.GetTitle(),
										 message.GetDescription(),
										 message.GetImageData(),
										 message.GetImageSize(),
										 message.GetShouldShare());
		}
    }
}
