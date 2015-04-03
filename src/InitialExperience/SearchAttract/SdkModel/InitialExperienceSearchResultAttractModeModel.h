// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInitialExperienceStep.h"
#include "Types.h"
#include "ICallback.h"
#include "IPersistentSettingsModel.h"
#include "BidirectionalBus.h"
#include "InitialExperienceSearchResultAttractModeModelStateExitedMessage.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SearchResultAttractMode
        {
            namespace SdkModel
            {
                class InitialExperienceSearchResultAttractModeModel : public InitialExperience::SdkModel::IInitialExperienceStep, private Eegeo::NonCopyable
                {
                public:
                    InitialExperienceSearchResultAttractModeModel(PersistentSettings::IPersistentSettingsModel& persistentSettings,
                                                                  ExampleAppMessaging::TMessageBus& messageBus);
                    
                    ~InitialExperienceSearchResultAttractModeModel();
                    
                    bool HasStarted() const;
                    
                    bool HasCompleted() const;
                    
                    void PerformInitialExperience();
                    
                    void EndInitialExperience();
                    
                    void Update(float deltaSeconds);
                    
                    void OnUiStateExitConditionsMet(const InitialExperienceSearchResultAttractModeModelStateExitedMessage& message);
                    
                private:
                    PersistentSettings::IPersistentSettingsModel& m_persistentSettings;
                    ExampleAppMessaging::TMessageBus& m_messageBus;
                    
                    Eegeo::Helpers::TCallback1<InitialExperienceSearchResultAttractModeModel, const InitialExperienceSearchResultAttractModeModelStateExitedMessage&> m_onUiStateExitConditionsMet;
                };
            }
        }
    }
}