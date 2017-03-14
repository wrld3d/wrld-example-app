// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InitialExperienceViewIncludes.h"
#include "InitialExperience.h"
#include "AndroidNativeState.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace View
		{
			class InitialExperienceIntroViewModule
			{
			public:
				InitialExperienceIntroViewModule(AndroidNativeState& nativeState, ExampleAppMessaging::TMessageBus& messageBus);
				~InitialExperienceIntroViewModule();

				InitialExperienceIntroController& GetController() { return *m_pController; }

			private:

				InitialExperienceIntroController* m_pController;
				InitialExperienceIntroView* m_pView;
			};
		}
	}
}
