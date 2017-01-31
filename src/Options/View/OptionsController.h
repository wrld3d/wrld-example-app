// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Options.h"
#include "ICallback.h"
#include "IOptionsViewModel.h"
#include "IOptionsView.h"
#include "BidirectionalBus.h"
#include "AppModeChangedMessage.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            class OptionsController : private Eegeo::NonCopyable
            {
            private:
                IOptionsView& m_view;
                IOptionsViewModel& m_viewModel;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                InteriorsExplorer::View::InteriorsExplorerController& m_interiorsExplorerController;

                Eegeo::Helpers::TCallback0<OptionsController> m_viewModelOpened;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewModelClosed;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewModelCacheClearCeremonyCompleted;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewCloseSelected;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewStreamOverWifiOnlySelectionChanged;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewCacheEnabledSelectionChanged;
                Eegeo::Helpers::TCallback0<OptionsController> m_viewClearCacheSelected;
                Eegeo::Helpers::TCallback1<OptionsController, const AppModes::AppModeChangedMessage&> m_appModeChangedHandler;
                Eegeo::Helpers::TCallback1<OptionsController, bool> m_replayTutorialsToggled;

                void OnViewModelOpened();

                void OnViewModelClosed();

                void OnViewModelCacheClearCeremonyCompleted();

                void OnViewCloseSelected();
                
                void OnViewStreamOverWifiOnlySelectionChanged();
                
                void OnViewCacheEnabledSelectionChanged();
                
                void OnViewClearCacheSelected();

                void OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message);

                void OnReplayTutorialsToggled(bool& replayTutorials);
            public:
                OptionsController(IOptionsView& view,
                                  IOptionsViewModel& viewModel,
                                  ExampleAppMessaging::TMessageBus& messageBus,
                                  InteriorsExplorer::View::InteriorsExplorerController& interiorsExplorerController);

                ~OptionsController();
            };
        }
    }
}
