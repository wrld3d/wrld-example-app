// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInitialExperienceStep.h"
#include "InitialExperience.h"
#include "BidirectionalBus.h"
#include "ICallback.h"
#include "PersistentSettings.h"
#include "InitialExperienceIntroDismissedMessage.h"
#include <string>

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            class InitialExperienceIntroStep : public IInitialExperienceStep
            {
            public:
                InitialExperienceIntroStep(ExampleAppMessaging::TMessageBus& messageBus,
                                           PersistentSettings::IPersistentSettingsModel& persistentSettings);
                ~InitialExperienceIntroStep();
                
                bool HasStarted() const;
                bool HasCompleted() const;
                void PerformInitialExperience();
                
                void ShowIntro();
                void Complete();
                void Update(float deltaSeconds);
                
            private:
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                PersistentSettings::IPersistentSettingsModel& m_persistentSettings;
                Eegeo::Helpers::TCallback1<InitialExperienceIntroStep, const InitialExperienceIntroDismissedMessage&> m_dismissedMessageHandler;
                
                bool m_currentlyShowingIntro;
                
                void OnIntroDismissed(const InitialExperienceIntroDismissedMessage& message);
            };
        }
    }
}