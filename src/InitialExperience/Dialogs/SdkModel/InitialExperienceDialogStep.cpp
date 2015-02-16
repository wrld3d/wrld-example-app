// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceDialogStep.h"
#include "IPersistentSettingsModel.h"
#include "ShowInitialExperienceDialogMessage.h"
#include <sstream>

namespace
{
    const std::string InitialExperienceModel_HasStartedDialog_Prefix = "InitialExperienceModel_HasStartedDialogKey_";

    const std::string InitialExperienceModel_HasCompletedDialog_Prefix = "InitialExperienceModel_HasCompletedDialogKey_";

    bool GetKeyValue(ExampleApp::PersistentSettings::IPersistentSettingsModel& persistentSettings, const std::string& key)
    {
        bool result = false;

        if(!persistentSettings.TryGetValue(key, result))
        {
            result = false;
        }

        return result;
    }

    std::string GetKeyStarted(ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::Values dialogType)
    {
    	std::stringstream sstm;
    	sstm << InitialExperienceModel_HasStartedDialog_Prefix << static_cast<int>(dialogType);
    	return sstm.str();
    }

    std::string GetKeyCompleted(ExampleApp::InitialExperience::Dialogs::InitialExperienceDialogType::Values dialogType)
	{
    	std::stringstream sstm;
		sstm << InitialExperienceModel_HasCompletedDialog_Prefix << static_cast<int>(dialogType);
		return sstm.str();
	}

    const float AppearAfterDelaySeconds = 1.0f;
}

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace Dialogs
		{
			namespace SdkModel
			{
				InitialExperienceDialogStep::InitialExperienceDialogStep(InitialExperienceDialogType::Values dialogType,
						ExampleAppMessaging::TMessageBus& messageBus,
						PersistentSettings::IPersistentSettingsModel& persistentSettings)
				: m_dialogType(dialogType)
				, m_messageBus(messageBus)
				, m_persistentSettings(persistentSettings)
				, m_persistentKeyStarted(GetKeyStarted(dialogType))
				, m_persistentKeyCompleted(GetKeyCompleted(dialogType))
				, m_dismissedMessageHandler(this, &InitialExperienceDialogStep::OnDialogDismissed)
				, m_currentlyShowingDialog(false)
				, m_delayTime(0.0f)
				{
					m_messageBus.SubscribeNative(m_dismissedMessageHandler);
				}

				InitialExperienceDialogStep::~InitialExperienceDialogStep()
				{
					m_messageBus.UnsubscribeNative(m_dismissedMessageHandler);
				}

				bool InitialExperienceDialogStep::HasStarted() const
				{
					return GetKeyValue(m_persistentSettings, m_persistentKeyStarted);
				}

				bool InitialExperienceDialogStep::HasCompleted() const
				{
					return GetKeyValue(m_persistentSettings, m_persistentKeyCompleted);
				}

				void InitialExperienceDialogStep::PerformInitialExperience()
				{
					Eegeo_ASSERT(!HasCompleted(), "Cannot perform InitialExperienceDialogStep, has already completed.\n");
					m_persistentSettings.SetValue(m_persistentKeyStarted, true);
				}

				void InitialExperienceDialogStep::ShowDialog()
				{
					m_currentlyShowingDialog = true;
					m_messageBus.Publish(ShowInitialExperienceDialogMessage(m_dialogType));
				}

				void InitialExperienceDialogStep::Complete()
				{
					Eegeo_ASSERT(!HasCompleted(), "Cannot perform InitialExperienceDialogStep, has already completed.\n");
					m_persistentSettings.SetValue(m_persistentKeyCompleted, true);
				}

				void InitialExperienceDialogStep::OnDialogDismissed(const InitialExperienceDialogDismissedMessage& message)
				{
					if(m_currentlyShowingDialog)
					{
						Complete();
						m_currentlyShowingDialog = false;
					}
				}

				void InitialExperienceDialogStep::Update(float deltaSeconds)
				{
					if(HasStarted() && !HasCompleted())
					{
						m_delayTime += deltaSeconds;
						if(!m_currentlyShowingDialog && m_delayTime >= AppearAfterDelaySeconds)
						{
							ShowDialog();
						}
					}
				}

			}
		}
	}
}
