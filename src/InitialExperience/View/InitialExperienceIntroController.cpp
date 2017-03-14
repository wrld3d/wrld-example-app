// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceIntroController.h"
#include "IInitialExperienceIntroView.h"
#include "InitialExperienceIntroDismissedMessage.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            InitialExperienceIntroController::InitialExperienceIntroController(IInitialExperienceIntroView& view, ExampleAppMessaging::TMessageBus& messageBus, bool isInKioskMode)
            : m_view(view)
            , m_messageBus(messageBus)
            , m_showIntroMessageHandler(this, &InitialExperienceIntroController::OnShowIntro)
            , m_viewDismissed(this, &InitialExperienceIntroController::OnViewDismissed)
            , m_isInKioskMode(isInKioskMode)
            , m_replayExitIUX(true)
            , m_exitIUXViewedCount(0)
            , m_currAppMode(AppModes::SdkModel::WorldMode)
            , m_appModeChangedHandler(this, &InitialExperienceIntroController::OnAppModeChangedMessage)
            {
                m_view.InsertDismissedCallback(m_viewDismissed);
                m_messageBus.SubscribeUi(m_showIntroMessageHandler);
                m_messageBus.SubscribeUi(m_appModeChangedHandler);
            }
            
            InitialExperienceIntroController::~InitialExperienceIntroController()
            {
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
                    AppModes::SdkModel::AppMode newAppMode = message.GetAppMode();
                    if(newAppMode == AppModes::SdkModel::AttractMode)
                    {
                        m_view.DismissExitIUX();
                        ReplayExitIUX(true);
                        m_exitIUXViewedCount = 0;
                    }
                    else if(newAppMode == AppModes::SdkModel::WorldMode && m_currAppMode == AppModes::SdkModel::InteriorMode)
                    {
                        const int maxTutorialViews = 2;
                        if(m_replayExitIUX || m_exitIUXViewedCount < maxTutorialViews)
                        {
                            m_view.ShowExitIUX();
                            ReplayExitIUX(false);
                            ++m_exitIUXViewedCount;
                        }
                    }

                    m_currAppMode = newAppMode;
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