// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInitialExperienceStep.h"
#include "InitialExperience.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "InitialExperienceDialogType.h"
#include "PersistentSettings.h"
#include "InitialExperienceDialogDismissedMessage.h"
#include <string>

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace Dialogs
		{
			namespace SdkModel
			{
				class InitialExperienceDialogStep : public InitialExperience::SdkModel::IInitialExperienceStep
				{
					public:
						InitialExperienceDialogStep(InitialExperienceDialogType::Values dialogType,
								ExampleAppMessaging::TMessageBus& messageBus,
								PersistentSettings::IPersistentSettingsModel& persistentSettings);
						~InitialExperienceDialogStep();

						bool HasStarted() const;
						bool HasCompleted() const;
						void PerformInitialExperience();

						void ShowDialog();
						void Complete();
						void Update(float deltaSeconds);

					private:

						const InitialExperienceDialogType::Values m_dialogType;
						ExampleAppMessaging::TMessageBus& m_messageBus;
						PersistentSettings::IPersistentSettingsModel& m_persistentSettings;
						Eegeo::Helpers::TCallback1<InitialExperienceDialogStep, const InitialExperienceDialogDismissedMessage&> m_dismissedMessageHandler;

						const std::string m_persistentKeyStarted;
						const std::string m_persistentKeyCompleted;

						bool m_currentlyShowingDialog;
						float m_delayTime;

						void OnDialogDismissed(const InitialExperienceDialogDismissedMessage& message);
				};
			}
		}
	}
}
