// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceDialogStepsFactory.h"
#include "InitialExperienceDialogStep.h"

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
						std::vector<InitialExperience::SdkModel::IInitialExperienceStep*>& out_steps)
					{
						out_steps.push_back(Eegeo_NEW(Dialogs::SdkModel::InitialExperienceDialogStep)(Dialogs::InitialExperienceDialogType::SearchMenu, messageBus, persistentSettings));
						out_steps.push_back(Eegeo_NEW(Dialogs::SdkModel::InitialExperienceDialogStep)(Dialogs::InitialExperienceDialogType::PrimaryMenu, messageBus, persistentSettings));
						out_steps.push_back(Eegeo_NEW(Dialogs::SdkModel::InitialExperienceDialogStep)(Dialogs::InitialExperienceDialogType::Compass, messageBus, persistentSettings));
						out_steps.push_back(Eegeo_NEW(Dialogs::SdkModel::InitialExperienceDialogStep)(Dialogs::InitialExperienceDialogType::PinCreation, messageBus, persistentSettings));
						out_steps.push_back(Eegeo_NEW(Dialogs::SdkModel::InitialExperienceDialogStep)(Dialogs::InitialExperienceDialogType::Flatten, messageBus, persistentSettings));
						out_steps.push_back(Eegeo_NEW(Dialogs::SdkModel::InitialExperienceDialogStep)(Dialogs::InitialExperienceDialogType::SourceCode, messageBus, persistentSettings));
					}
				}
			}
		}
	}
}
