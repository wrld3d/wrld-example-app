// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "MyPinCreationModelObserver.h"

namespace ExampleApp
{
    namespace MyPinCreation
    {
    	MyPinCreationModelObserver::MyPinCreationModelObserver(IMyPinCreationModel& myPinCreationModel,
								   ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
		: m_myPinCreationModel(myPinCreationModel)
		, m_nativeToUiMessageBus(nativeToUiMessageBus)
		, m_callback(this, &MyPinCreationModelObserver::HandlePoiCreationModelStateChange)
		{
			m_myPinCreationModel.AddStateChangedCallback(m_callback);
		}

    	MyPinCreationModelObserver::~MyPinCreationModelObserver()
		{
			m_myPinCreationModel.RemoveStateChangedCallback(m_callback);
		}

		void MyPinCreationModelObserver::HandlePoiCreationModelStateChange(MyPinCreationStage& stage)
		{
			m_nativeToUiMessageBus.Publish(MyPinCreationStateChangedMessage(stage));
		}
    }
}
