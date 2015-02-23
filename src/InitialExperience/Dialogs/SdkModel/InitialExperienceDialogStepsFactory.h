// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInitialExperienceStep.h"
#include "BidirectionalBus.h"
#include "PersistentSettings.h"
#include <vector>

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace Dialogs
		{
			namespace SdkModel
			{
				namespace InitialExperienceDialogStepsFactory
				{
					void AddInitialExperienceDialogSteps(
							ExampleAppMessaging::TMessageBus& messageBus,
							PersistentSettings::IPersistentSettingsModel& persistentSettings,
							std::vector<InitialExperience::SdkModel::IInitialExperienceStep*>& out_steps);
				}
			}
		}
	}
}
