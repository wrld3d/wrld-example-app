// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorsExplorer.h"
#include "BidirectionalBus.h"
#include "Menu.h"
#include "MyPinCreation.h"
#include "ScreenControlViewModelIncludes.h"
#include "InteriorsExplorerStateChangedMessage.h"
#include "InteriorsExplorerFloorSelectedMessage.h"
#include "InteriorsExplorerInteriorStreamingMessage.h"
#include "IAppModeModel.h" // FM: Included for definition of AppMode, may want to extract AppMode to separate .h
#include <sstream>
#include "InteriorsExplorerUINotifyMessage.h"
#include "NavigationService.h"
#include "InitialExperienceIntroDismissedMessage.h"
#include "ShowInitialExperienceIntroMessage.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class InteriorsExplorerController
            {
            public:
                
                InteriorsExplorerController(SdkModel::InteriorsExplorerModel& model,
                                            IInteriorsExplorerView& view,
                                            InteriorsExplorerViewModel& viewModel,
                                            IInteriorStreamingDialogView& streamingDialogView,
                                            ExampleAppMessaging::TMessageBus& messageBus,
                                            Eegeo::Location::NavigationService& navigationService);
                
                ~InteriorsExplorerController();

                void ReplayTutorials(const bool enableTutorials);
                void InsertReplayTutorialsChangedCallback(Eegeo::Helpers::ICallback1<bool>& callback);
                void RemoveReplayTutorialsChangedCallback(Eegeo::Helpers::ICallback1<bool>& callback);
                
            private:
                
                void OnDismiss();
                void OnSelectFloor(int& selected);
                void OnFloorSelectionDragged(float& dragParam);
                void OnInteriorStreaming(const InteriorsExplorerInteriorStreamingMessage& message);
                void OnFloorSelected(const InteriorsExplorerFloorSelectedMessage& message);
                void OnStateChanged(const InteriorsExplorerStateChangedMessage& message);
                void OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel &viewModel);
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
                void OnInteriorsUINotificationRequired(const InteriorsExplorerUINotifyMessage& message);
                void TryShowTutorials();
                void OnIntroDismissed(const InitialExperience::InitialExperienceIntroDismissedMessage& message);
                void OnShowIntro(const InitialExperience::ShowInitialExperienceIntroMessage& message);
                
                SdkModel::InteriorsExplorerModel& m_model;
                IInteriorsExplorerView& m_view;
                InteriorsExplorerViewModel& m_viewModel;
                IInteriorStreamingDialogView& m_streamingDialogView;
                bool m_replayTutorials;
                bool m_shouldShowTutorialsAfterWelcomeUX;
                bool m_currentlyShowingIntro;
                Eegeo::Helpers::CallbackCollection1<bool> m_replayTutorialsCallbacks;
                
                Eegeo::Helpers::TCallback0<InteriorsExplorerController> m_dismissedCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, int> m_selectFloorCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, float> m_draggingFloorSelectionCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, const InteriorsExplorerInteriorStreamingMessage&> m_interiorStreamingCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, const InteriorsExplorerStateChangedMessage&> m_stateChangedCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, const InteriorsExplorerFloorSelectedMessage&> m_floorSelectedCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, ScreenControl::View::IScreenControlViewModel&> m_viewStateCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, const InteriorsExplorerUINotifyMessage&> m_interiorsUINotificationCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, const InitialExperience::InitialExperienceIntroDismissedMessage&> m_dismissedMessageHandler;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, const InitialExperience::ShowInitialExperienceIntroMessage&> m_showIntroMessageHandler;

                AppModes::SdkModel::AppMode m_appMode;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Location::NavigationService& m_navigationService;
            };
        }
    }
}
