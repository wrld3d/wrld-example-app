// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorsExplorer.h"
#include "BidirectionalBus.h"
#include "Menu.h"
#include "MyPinCreation.h"
#include "ScreenControlViewModelIncludes.h"
#include "InteriorsExplorerStateChangedMessage.h"
#include "InteriorsExplorerFloorSelectedMessage.h"
#include "IAppModeModel.h" // FM: Included for definition of AppMode, may want to extract AppMode to separate .h
#include <sstream>
#include "InteriorsExplorerUINotifyMessage.h"
#include "NavigationService.h"

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
                void OnFloorSelected(const InteriorsExplorerFloorSelectedMessage& message);
                void OnStateChanged(const InteriorsExplorerStateChangedMessage& message);
                void OnViewStateChangeScreenControl(ScreenControl::View::IScreenControlViewModel &viewModel, float &state);
                void OnAppModeChanged(const AppModes::AppModeChangedMessage& message);
                void OnInteriorsUINotificationRequired(const InteriorsExplorerUINotifyMessage& message);
                
                SdkModel::InteriorsExplorerModel& m_model;
                IInteriorsExplorerView& m_view;
                InteriorsExplorerViewModel& m_viewModel;
                bool m_replayTutorials;
                Eegeo::Helpers::CallbackCollection1<bool> m_replayTutorialsCallbacks;
                
                Eegeo::Helpers::TCallback0<InteriorsExplorerController> m_dismissedCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, int> m_selectFloorCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, float> m_draggingFloorSelectionCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, const InteriorsExplorerStateChangedMessage&> m_stateChangedCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, const InteriorsExplorerFloorSelectedMessage&> m_floorSelectedCallback;
                Eegeo::Helpers::TCallback2<InteriorsExplorerController, ScreenControl::View::IScreenControlViewModel&, float> m_viewStateCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, const AppModes::AppModeChangedMessage&> m_appModeChangedCallback;
                Eegeo::Helpers::TCallback1<InteriorsExplorerController, const InteriorsExplorerUINotifyMessage&> m_interiorsUINotificationCallback;

                AppModes::SdkModel::AppMode m_appMode;
                
                ExampleAppMessaging::TMessageBus& m_messageBus;

                Eegeo::Location::NavigationService& m_navigationService;
            };
        }
    }
}
