// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

//#include "InitialExperienceViewIncludes.h"
//#include "InitialExperience.h"
//#include "AndroidNativeState.h"
//#include "BidirectionalBus.h"

#include "Module.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace View
		{
			class InitialExperienceIntroViewModule : public Module
			{
			public:
				void Register(const TContainerBuilder& builder);
//			public:
//				InitialExperienceIntroViewModule(AndroidNativeState& nativeState, ExampleAppMessaging::TMessageBus& messageBus);
//				~InitialExperienceIntroViewModule();
//
//
//			private:
//
//				InitialExperienceIntroController* m_pController;
//				InitialExperienceIntroView* m_pView;
			};
		}
	}
}
