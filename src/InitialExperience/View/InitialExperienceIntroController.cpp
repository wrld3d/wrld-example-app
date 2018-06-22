// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceIntroController.h"
#include "IInitialExperienceIntroView.h"
#include "InitialExperienceIntroDismissedMessage.h"
#include "ICameraTransitionController.h"
#include "INavWidgetViewModel.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            namespace
            {
                const int maxTutorialViews = 2;
            }

            InitialExperienceIntroController::InitialExperienceIntroController(IInitialExperienceIntroView& view,
                                                                               ExampleAppMessaging::TMessageBus& messageBus,
                                                                               NavRouting::View::INavWidgetViewModel& navWidgetViewModel,
                                                                               CameraTransitions::SdkModel::ICameraTransitionController& cameraTransitionController)
            : m_view(view)
            , m_messageBus(messageBus)
            , m_navWidgetViewModel(navWidgetViewModel)
            , m_showIntroMessageHandler(this, &InitialExperienceIntroController::OnShowIntro)
            , m_viewDismissed(this, &InitialExperienceIntroController::OnViewDismissed)
            , m_replayExitIUX(false)
            , m_navWidgetOpen(false)
            , m_exitIUXViewedCount(maxTutorialViews)
            , m_currAppMode(AppModes::SdkModel::WorldMode)
            , m_shouldShowExitIUX(false)
            , m_appModeChangedHandler(this, &InitialExperienceIntroController::OnAppModeChangedMessage)
            , m_cameraTransitionController(cameraTransitionController)
            , m_transitionCompleteHandler(this, &InitialExperienceIntroController::OnTransitionCompleteHandler)
            , m_navWidgetOpenedHandler(this, &InitialExperienceIntroController::OnNavWidgetOpened)
            , m_navWidgetClosedHandler(this, &InitialExperienceIntroController::OnNavWidgetClosed)
            {
                m_view.InsertDismissedCallback(m_viewDismissed);
                m_navWidgetViewModel.InsertOpenedCallback(m_navWidgetOpenedHandler);
                m_navWidgetViewModel.InsertClosedCallback(m_navWidgetClosedHandler);
                m_messageBus.SubscribeUi(m_showIntroMessageHandler);
                m_messageBus.SubscribeUi(m_appModeChangedHandler);

                // THREAD SAFETY CONCERN
                m_cameraTransitionController.InsertTransitioningChangedCallback(m_transitionCompleteHandler);
            }
            
            InitialExperienceIntroController::~InitialExperienceIntroController()
            {
                m_cameraTransitionController.RemoveTransitioningChangedCallback(m_transitionCompleteHandler);

                m_messageBus.UnsubscribeUi(m_appModeChangedHandler);
                m_messageBus.UnsubscribeUi(m_showIntroMessageHandler);
                
                m_navWidgetViewModel.RemoveClosedCallback(m_navWidgetClosedHandler);
                m_navWidgetViewModel.RemoveOpenedCallback(m_navWidgetOpenedHandler);
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
					if (m_cameraTransitionController.IsTransitioning() || m_navWidgetOpen)
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
            
            void InitialExperienceIntroController::OnNavWidgetOpened()
            {
                m_navWidgetOpen = true;
            }
            
            void InitialExperienceIntroController::OnNavWidgetClosed()
            {
                m_navWidgetOpen = false;
                if(m_shouldShowExitIUX)
                {
                    m_shouldShowExitIUX = false;
                    ShowExitIUX();
                }
            }

            void InitialExperienceIntroController::OnTransitionCompleteHandler()
            {
                if (!m_cameraTransitionController.IsTransitioning() && m_shouldShowExitIUX && !m_navWidgetOpen)
                {
                    m_shouldShowExitIUX = false;
                    ShowExitIUX();
                }
            }

            void InitialExperienceIntroController::ShowExitIUX()
            {
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
