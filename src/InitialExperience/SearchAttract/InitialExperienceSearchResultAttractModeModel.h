// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInitialExperienceStep.h"
#include "Types.h"
#include "ISearchResultMenuViewModel.h"
#include "ICallback.h"
#include "ScreenControlViewModelIncludes.h"
#include "OpenableControlViewModelIncludes.h"
#include "IPersistentSettingsModel.h"
#include "BidirectionalBus.h"
#include "InitialExperienceSearchResultAttractModeModelStateEnteredMessage.h"
#include "InitialExperienceSearchResultAttractModeModelStateUpdatedMessage.h"
#include "InitialExperienceSearchResultAttractModeModelStateExitedMessage.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SearchResultAttractMode
        {
            class InitialExperienceSearchResultAttractModeModel : public InitialExperience::SdkModel::IInitialExperienceStep, private Eegeo::NonCopyable
            {
            public:
                InitialExperienceSearchResultAttractModeModel(PersistentSettings::IPersistentSettingsModel& persistentSettings,
                                                              Menu::View::IMenuViewModel& searchMenuViewModelControl,
                                                              SearchResultMenu::View::ISearchResultMenuViewModel& searchResultMenuViewModel,
                                                              ExampleAppMessaging::TMessageBus& messageBus);
                
                ~InitialExperienceSearchResultAttractModeModel();
                
                void OnSearchResultMenuOpenStateChange(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState);
                
                bool HasStarted() const;
                
                bool HasCompleted() const;
                
                void PerformInitialExperience();
                
                void EndInitialExperience();
                
                void Update(float deltaSeconds);
                
                void SetAttractStateBaseOnInteractivity();
                
                void EnterInitialExperienceUi();
                
                void UpdateUi();
                
                void ExitInitialExperienceUi();
                
                void OnNativeStateEntered(const InitialExperienceSearchResultAttractModeModelStateEnteredMessage& message);
                
                void OnNativeStateUpdated(const InitialExperienceSearchResultAttractModeModelStateUpdatedMessage& message);
                
                void OnUiStateExitConditionsMet(const InitialExperienceSearchResultAttractModeModelStateExitedMessage& message);
                
            private:
                PersistentSettings::IPersistentSettingsModel& m_persistentSettings;
                Menu::View::IMenuViewModel& m_searchMenuViewModelControl;
                SearchResultMenu::View::ISearchResultMenuViewModel& m_searchResultMenuViewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                bool m_shouldEnd;
                bool m_finished;
                
                Eegeo::Helpers::TCallback2<InitialExperienceSearchResultAttractModeModel, OpenableControl::View::IOpenableControlViewModel&, float> m_onOpenableStateChanged;

                Eegeo::Helpers::TCallback1<InitialExperienceSearchResultAttractModeModel, const InitialExperienceSearchResultAttractModeModelStateEnteredMessage&> m_onNativeStateEntered;
                
                Eegeo::Helpers::TCallback1<InitialExperienceSearchResultAttractModeModel, const InitialExperienceSearchResultAttractModeModelStateUpdatedMessage&> m_onNativeStateUpdated;
                
                Eegeo::Helpers::TCallback1<InitialExperienceSearchResultAttractModeModel, const InitialExperienceSearchResultAttractModeModelStateExitedMessage&> m_onUiStateExitConditionsMet;
            };
        }
    }
}