//  Copyright (c) 2014 eeGeo. All rights reserved.

#include "CompassViewCycledObserver.h"

namespace ExampleApp
{
	namespace Compass
	{
		CompassViewCycledObserver::CompassViewCycledObserver(ICompassModel& model,
								  ExampleApp::ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus
								 )
			: m_model(model)
			, m_uiToNativeMessageBus(uiToNativeMessageBus)
			, m_handler(this, &CompassViewCycledObserver::OnCompassCycled)
		{
			m_uiToNativeMessageBus.Subscribe(m_handler);
		}

		CompassViewCycledObserver::~CompassViewCycledObserver()
		{
			m_uiToNativeMessageBus.Unsubscribe(m_handler);
		}

		void CompassViewCycledObserver::OnCompassCycled(const CompassViewCycledMessage& message)
		{
			m_model.CycleToNextGpsMode();
		}
	}
}
