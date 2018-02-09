// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Options.h"
#include "ICallback.h"
#include "IOptionsViewModel.h"
#include "IOptionsView.h"
#include "BidirectionalBus.h"
#include "AppModeChangedMessage.h"
#include "InteriorsExplorer.h"
#include "InitialExperienceIntroController.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            class OptionsController : private Eegeo::NonCopyable
            {
            private:
                template<typename T>
                class Change
                {
                    T m_oldValue;
                    T m_newValue;
                public:
					Change(T safeDummyValue)	{ Init(safeDummyValue); }
                    void Init(T initialValue)   { m_oldValue = m_newValue = initialValue; }
                    T    GetValue()             { return m_newValue; }
                    void SetValue(T value)      { m_newValue = value; }
                    bool HasChanged()           { return m_newValue != m_oldValue; }
                };

                Change<bool> m_valueOfStreamOverWifiOnly;
                Change<bool> m_valueOfCachingEnabled;
                Change<bool> m_valueOfClearCacheSelected;
                Change<bool> m_valueOfPlayTutorialAgainSelected;

                IOptionsView& m_view;
                IOptionsViewModel& m_viewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                InteriorsExplorer::View::InteriorsExplorerController& m_interiorsExplorerController;
                InitialExperience::View::InitialExperienceIntroController& m_initialExperienceIntroController;
                int m_tutorialsReplayedCount;

                Eegeo::Helpers::TCallback0<OptionsController> m_viewModelOpened;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewModelClosed;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewModelCacheClearCeremonyCompleted;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewCloseSelected;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewOkSelected;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewStreamOverWifiOnlySelectionChanged;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewCacheEnabledSelectionChanged;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewClearCacheSelectionChanged;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewClearCacheTriggered;
                Eegeo::Helpers::TCallback1<OptionsController, const AppModes::AppModeChangedMessage&> m_appModeChangedHandler;
                Eegeo::Helpers::TCallback1<OptionsController, bool> m_replayTutorialsToggled;
                Eegeo::Helpers::TCallback1<OptionsController, bool> m_onReplayTutorialsModelChanged;
                Eegeo::Helpers::TCallback1<OptionsController, const DeepLink::DeepLinkOpenedMessage&> m_deepLinkOpenedHandler;

                void OnViewModelOpened();

                void OnViewModelClosed();

                void OnViewModelCacheClearCeremonyCompleted();

                void OnViewCloseSelected();

                void OnViewOkSelected();

                void OnViewStreamOverWifiOnlySelectionChanged();
                
                void OnViewCacheEnabledSelectionChanged();
                
                void OnViewClearCacheSelectionChanged();

                void OnViewClearCacheTriggered();

                void OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message);

                void OnReplayTutorialsToggled(bool& replayTutorials);

                void OnReplayTutorialsModelChanged(bool& replayTutorials);
                
                void OnDeepLinkOpenedMessage(const DeepLink::DeepLinkOpenedMessage& message);
            public:
                OptionsController(IOptionsView& view,
                                  IOptionsViewModel& viewModel,
                                  ExampleAppMessaging::TMessageBus& messageBus,
                                  InteriorsExplorer::View::InteriorsExplorerController& interiorsExplorerController,
                                  InitialExperience::View::InitialExperienceIntroController& initialExperienceIntroController);

                ~OptionsController();
            };
        }
    }
}
