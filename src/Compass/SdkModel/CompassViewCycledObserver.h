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

			void OnCompassCycled(const CompassViewCycledMessage& message);

		public:
			CompassViewCycledObserver(ICompassModel& model,
			                          ExampleApp::ExampleAppMessaging::UiToNativeMessageBus& uiToNativeMessageBus
			                         );

			~CompassViewCycledObserver();
		};
	}
}
