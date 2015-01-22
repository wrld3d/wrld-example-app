// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ModalityObserver.h"

namespace ExampleApp
{
	namespace Modality
	{
		ModalityObserver::ModalityObserver(IModalityModel& modalityModel,
						 ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus)
			: m_modalityModel(modalityModel)
			, m_uiToNativeMessageBus(uiToNativeMessageBus)
			, m_modalityChangedCallback(this, &ModalityObserver::HandleModalityChanged)
		{
			m_modalityModel.InsertModalityChangedCallback(m_modalityChangedCallback);
		}

		ModalityObserver::~ModalityObserver()
		{
			m_modalityModel.RemoveModalityChangedCallback(m_modalityChangedCallback);
		}

		void ModalityObserver::HandleModalityChanged()
		{
			m_uiToNativeMessageBus.Publish(ModalityChangedMessage(m_modalityModel.GetModality()));
		}
	}
}
