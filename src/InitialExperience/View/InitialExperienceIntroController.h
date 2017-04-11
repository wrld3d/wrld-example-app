// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "BidirectionalBus.h"
#include "InitialExperience.h"
#include "ShowInitialExperienceIntroMessage.h"
#include "CameraTransitions.h"
#include <string>

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            class InitialExperienceIntroController
            {
            public:
             
                InitialExperienceIntroController(IInitialExperienceIntroView& view,
                                                 ExampleAppMessaging::TMessageBus& messageBus,
                                                 bool isInKioskMode,
                                                 CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController);
                ~InitialExperienceIntroController();

                void ReplayExitIUX(const bool enableExitIUX);

                void InsertReplayExitIUXChangedCallback(Eegeo::Helpers::ICallback1<bool>& callback);
                void RemoveReplayExitIUXChangedCallback(Eegeo::Helpers::ICallback1<bool>& callback);
                
            private:
                
                ExampleAppMessaging::TMessageBus& m_messageBus;
                IInitialExperienceIntroView& m_view;
                
                Eegeo::Helpers::TCallback1<InitialExperienceIntroController, const ShowInitialExperienceIntroMessage&> m_showIntroMessageHandler;
                Eegeo::Helpers::TCallback0<InitialExperienceIntroController> m_viewDismissed;
                
                void OnShowIntro(const ShowInitialExperienceIntroMessage& message);
                void OnViewDismissed();

                bool m_isInKioskMode;

                bool m_replayExitIUX;
                int m_exitIUXViewedCount;
                AppModes::SdkModel::AppMode m_currAppMode;

                Eegeo::Helpers::CallbackCollection1<bool> m_replayExitIUXCallbacks;

                Eegeo::Helpers::TCallback1<InitialExperienceIntroController, const AppModes::AppModeChangedMessage&> m_appModeChangedHandler;
                void OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message);

                void ShowExitIUX();

                bool m_shouldShowExitIUX;

                CameraTransitions::SdkModel::ICameraTransitionController& m_cameraTransitionController;
                Eegeo::Helpers::TCallback0<InitialExperienceIntroController> m_transitionCompleteHandler;
                void OnTransitionCompleteHandler();
            
            };
        }
    }
}