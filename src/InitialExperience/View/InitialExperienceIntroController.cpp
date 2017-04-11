// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceIntroController.h"
#include "IInitialExperienceIntroView.h"
#include "InitialExperienceIntroDismissedMessage.h"
#include "ICameraTransitionController.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            InitialExperienceIntroController::InitialExperienceIntroController(IInitialExperienceIntroView& view,
                                                                               ExampleAppMessaging::TMessageBus& messageBus,
                                                                               bool isInKioskMode,
                                                                               CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController)
            : m_view(view)
            , m_messageBus(messageBus)
            , m_showIntroMessageHandler(this, &InitialExperienceIntroController::OnShowIntro)
            , m_viewDismissed(this, &InitialExperienceIntroController::OnViewDismissed)
            , m_isInKioskMode(isInKioskMode)
            , m_replayExitIUX(true)
            , m_exitIUXViewedCount(0)
            , m_currAppMode(AppModes::SdkModel::WorldMode)
            , m_shouldShowExitIUX(false)
            , m_appModeChangedHandler(this, &InitialExperienceIntroController::OnAppModeChangedMessage)
            , m_cameraTransitionController(cameraTransitionController)
            , m_transitionCompleteHandler(this, &InitialExperienceIntroController::OnTransitionCompleteHandler)
            {
                m_view.InsertDismissedCallback(m_viewDismissed);
                m_messageBus.SubscribeUi(m_showIntroMessageHandler);
                m_messageBus.SubscribeUi(m_appModeChangedHandler);

                m_cameraTransitionController.InsertTransitioningChangedCallback(m_transitionCompleteHandler);
            }
            
            InitialExperienceIntroController::~InitialExperienceIntroController()
            {
                m_cameraTransitionController.RemoveTransitioningChangedCallback(m_transitionCompleteHandler);

                m_messageBus.UnsubscribeUi(m_appModeChangedHandler);
                m_messageBus.UnsubscribeUi(m_showIntroMessageHandler);
                m_view.RemoveDismissedCallback(m_viewDismissed);
            }
            
            void InitialExperienceIntroController::OnShowIntro(const ShowInitialExperienceIntroMessage& message)
            {
                m_view.Show();
            }
            
            void InitialExperienceIntroController::OnViewDismissed()
            {
                m_messageBus.Publish(InitialExperienceIntroDismissedMessage());
            }

            void InitialExperienceIntroController::OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message)
            {
                if(m_isInKioskMode)
                {
                    m_shouldShowExitIUX = false;

                    AppModes::SdkModel::AppMode newAppMode = message.GetAppMode();
                    if(newAppMode == AppModes::SdkModel::AttractMode)
                    {
                        m_view.DismissExitIUX();
                        ReplayExitIUX(true);
                        m_exitIUXViewedCount = 0;
                    }
                    else if(newAppMode == AppModes::SdkModel::WorldMode && m_currAppMode == AppModes::SdkModel::InteriorMode)
                    {
                        if (m_cameraTransitionController.IsTransitioning())
                        {
                            m_shouldShowExitIUX = true;
                        }
                        else
                        {
                            ShowExitIUX();
                        }
                    }

                    m_currAppMode = newAppMode;
                }
            }

            void InitialExperienceIntroController::OnTransitionCompleteHandler()
            {
                if (!m_cameraTransitionController.IsTransitioning() && m_shouldShowExitIUX)
                {
                    m_shouldShowExitIUX = false;
                    ShowExitIUX();
                }
            }

            void InitialExperienceIntroController::ShowExitIUX()
            {
                const int maxTutorialViews = 2;
                if(m_replayExitIUX || m_exitIUXViewedCount < maxTutorialViews)
                {
                    m_view.ShowExitIUX();
                    ReplayExitIUX(false);
                    ++m_exitIUXViewedCount;
                }
            }

            void InitialExperienceIntroController::ReplayExitIUX(const bool enableTutorials)
            {
                m_replayExitIUX = enableTutorials;
                m_replayExitIUXCallbacks.ExecuteCallbacks(m_replayExitIUX);
            }

            void InitialExperienceIntroController::InsertReplayExitIUXChangedCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_replayExitIUXCallbacks.AddCallback(callback);
            }

            void InitialExperienceIntroController::RemoveReplayExitIUXChangedCallback(Eegeo::Helpers::ICallback1<bool>& callback)
            {
                m_replayExitIUXCallbacks.RemoveCallback(callback);
            }
        }
    }
}