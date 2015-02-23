// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InitialExperienceDialogs.h"
#include "InitialExperienceDialogsViewIncludes.h"
#include "AndroidNativeState.h"
#include "BidirectionalBus.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace Dialogs
		{
			namespace View
			{
				class InitialExperienceDialogsViewModule
				{
				public:
					InitialExperienceDialogsViewModule(
							AndroidNativeState& nativeState,
							IInitialExperienceDialogsViewModel& viewModel,
							ExampleAppMessaging::TMessageBus& messageBus);
					~InitialExperienceDialogsViewModule();

				private:

					InitialExperienceDialogsView* m_pView;
					InitialExperienceDialogsController* m_pController;

				};
			}
		}
	}
}
