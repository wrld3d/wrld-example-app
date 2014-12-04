// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationViewStateChangedHandler.h"
#include "ISearchRefreshService.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
		MyPinCreationViewStateChangedHandler::MyPinCreationViewStateChangedHandler(IMyPinCreationModel& myPinCreationModel,
                                                 Search::ISearchRefreshService& searchRefreshService,
											     ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
		: m_myPinCreationModel(myPinCreationModel)
        , m_searchRefreshService(searchRefreshService)
		, m_uiToNativeMessageBus(uiToNativeMessageBus)
		, m_handler(this, &MyPinCreationViewStateChangedHandler::OnMyPinCreationViewStateChangedMessageReceived)
		{
			m_uiToNativeMessageBus.Subscribe(m_handler);
		}

		MyPinCreationViewStateChangedHandler::~MyPinCreationViewStateChangedHandler()
		{
			m_uiToNativeMessageBus.Unsubscribe(m_handler);
		}

		void MyPinCreationViewStateChangedHandler::OnMyPinCreationViewStateChangedMessageReceived(const MyPinCreationViewStateChangedMessage& message)
		{
			m_myPinCreationModel.SetCreationStage(message.GetMyPinCreationStage());
            m_searchRefreshService.SetEnabled(message.GetMyPinCreationStage() == MyPinCreation::Inactive);
		}
    }
}
