//  Copyright (c) 2014 eeGeo. All rights reserved.

#include "CompassModeObserver.h"

namespace ExampleApp
{
	namespace Compass
	{
		CompassModeObserver::CompassModeObserver(ICompassModel& model,
							ExampleApp::ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
			: m_model(model)
			, m_nativeToUiMessageBus(nativeToUiMessageBus)
			, m_callback(this, &CompassModeObserver::OnGpsModeChanged)
		{
			m_model.InsertGpsModeChangedCallback(m_callback);
		}

		CompassModeObserver::~CompassModeObserver()
		{
			m_model.RemoveGpsModeChangedCallback(m_callback);
		}

		void CompassModeObserver::OnGpsModeChanged()
		{
			m_nativeToUiMessageBus.Publish(CompassModeChangedMessage(m_model.GetGpsMode()));
		}
	}
}
