//  Copyright (c) 2014 eeGeo. All rights reserved.

#pragma once

#include "Types.h"
#include "UiToNativeMessageBus.h"
#include "CompassViewCycledMessage.h"
#include "ICompassModel.h"
#include "ICallback.h"

namespace ExampleApp
{
	namespace Compass
	{
		class CompassViewCycledObserver : private Eegeo::NonCopyable
		{
		private:
			ExampleApp::ExampleAppMessaging::UiToNativeMessageBus& m_uiToNativeMessageBus;
			ICompassModel& m_model;
			Eegeo::Helpers::TCallback1<CompassViewCycledObserver, const CompassViewCycledMessage&> m_handler;

			void OnCompassCycled(const CompassViewCycledMessage& message)
			{
				m_model.CycleToNextGpsMode();
			}

		public:
			CompassViewCycledObserver(ICompassModel& model,
			                          ExampleApp::ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus
			                         )
				: m_model(model)
				, m_uiToNativeMessageBus(uiToNativeMessageBus)
				, m_handler(this, &CompassViewCycledObserver::OnCompassCycled)
			{
				m_uiToNativeMessageBus.Subscribe(m_handler);
			}

			~CompassViewCycledObserver()
			{
				m_uiToNativeMessageBus.Unsubscribe(m_handler);
			}
		};
	}
}