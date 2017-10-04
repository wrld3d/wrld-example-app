// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "OptionsController.h"
#include "StreamOverWifiOnlyChangedMessage.h"
#include "CacheEnabledChangedMessage.h"
#include "ClearCacheMessage.h"
#include "InteriorsExplorerController.h"

namespace ExampleApp
{
    namespace Options
    {
        namespace View
        {
            void OptionsController::OnViewModelOpened()
            {
                if (m_viewModel.TryAcquireReactorControl())
                {
                    m_view.Open();
                }
            }

            void OptionsController::OnViewModelClosed()
            {
                m_view.Close();
            }
            
            void OptionsController::OnViewModelCacheClearCeremonyCompleted()
            {
                m_view.ConcludeCacheClearCeremony();
            }

            void OptionsController::OnViewCloseSelected()
            {
                if (m_viewModel.IsOpen())
                {
                    m_viewModel.Close();
                }
            }
            
            void OptionsController::OnViewStreamOverWifiOnlySelectionChanged()
            {
                m_messageBus.Publish(StreamOverWifiOnlyChangedMessage(m_view.IsStreamOverWifiOnlySelected()));
            }
            
            void OptionsController::OnViewCacheEnabledSelectionChanged()
            {
                m_messageBus.Publish(CacheEnabledChangedMessage(m_view.IsCacheEnabledSelected()));
            }
            
            void OptionsController::OnViewClearCacheSelected()
            {
                m_viewModel.BeginCacheClearCeremony();
                
                m_messageBus.Publish(ClearCacheMessage());
            }

            void OptionsController::OnReplayTutorialsToggled(bool& enableTutorials)
            {
                m_interiorsExplorerController.ReplayTutorials(enableTutorials);
                m_initialExperienceIntroController.ReplayExitIUX(enableTutorials);
            }

            void OptionsController::OnReplayTutorialsModelChanged(bool& enableTutorials)
            {
                if(enableTutorials)
                {
                    m_tutorialsReplayedCount = 0;
                    m_view.SetReplayTutorialsSelected(enableTutorials);
                }
                else
                {
                    ++m_tutorialsReplayedCount;
                    const int tutorialCount = 2;
                    if(m_tutorialsReplayedCount >= tutorialCount)
                    {
                        m_view.SetReplayTutorialsSelected(enableTutorials);
                    }
                }
            }

            void OptionsController::OnAppModeChanged(const AppModes::AppModeChangedMessage &message)
            {
                if (message.GetAppMode() == AppModes::SdkModel::AppMode::AttractMode && m_viewModel.IsOpen())
                {
                    m_viewModel.Close();
                }
            }
            
            OptionsController::OptionsController(IOptionsView& view,
                                                 IOptionsViewModel& viewModel,
                                                 ExampleAppMessaging::TMessageBus& messageBus,
                                                 InteriorsExplorer::View::InteriorsExplorerController& interiorsExplorerController,
                                                 InitialExperience::View::InitialExperienceIntroController& initialExperienceIntroController)
            : m_view(view)
            , m_viewModel(viewModel)
            , m_messageBus(messageBus)
            , m_interiorsExplorerController(interiorsExplorerController)
            , m_initialExperienceIntroController(initialExperienceIntroController)
            , m_tutorialsReplayedCount(0)
            , m_viewModelClosed(this, &OptionsController::OnViewModelClosed)
            , m_viewModelOpened(this, &OptionsController::OnViewModelOpened)
            , m_viewModelCacheClearCeremonyCompleted(this, &OptionsController::OnViewModelCacheClearCeremonyCompleted)
            , m_viewCloseSelected(this, &OptionsController::OnViewCloseSelected)
            , m_viewStreamOverWifiOnlySelectionChanged(this, &OptionsController::OnViewStreamOverWifiOnlySelectionChanged)
            , m_viewCacheEnabledSelectionChanged(this, &OptionsController::OnViewCacheEnabledSelectionChanged)
            , m_viewClearCacheSelected(this, &OptionsController::OnViewClearCacheSelected)
            , m_replayTutorialsToggled(this, &OptionsController::OnReplayTutorialsToggled)
            , m_onReplayTutorialsModelChanged(this, &OptionsController::OnReplayTutorialsModelChanged)
            , m_appModeChangedMessageHandler(this, &OptionsController::OnAppModeChanged)
            {
                m_view.InsertCloseSelectedCallback(m_viewCloseSelected);
                m_view.InsertStreamOverWifiOnlySelectionChangedCallback(m_viewStreamOverWifiOnlySelectionChanged);
                m_view.InsertCacheEnabledSelectionCallback(m_viewCacheEnabledSelectionChanged);
                m_view.InsertClearCacheSelectedCallback(m_viewClearCacheSelected);
                m_view.InsertReplayTutorialsToggledCallback(m_replayTutorialsToggled);
                
                m_viewModel.InsertClosedCallback(m_viewModelClosed);
                m_viewModel.InsertOpenedCallback(m_viewModelOpened);
                m_viewModel.InsertCacheClearCeremonyCompletedCallback(m_viewModelCacheClearCeremonyCompleted);

                m_view.SetStreamOverWifiOnlySelected(m_viewModel.StreamOverWifiOnly());
                m_view.SetCacheEnabledSelected(m_viewModel.CachingEnabled());

                m_interiorsExplorerController.InsertReplayTutorialsChangedCallback(m_onReplayTutorialsModelChanged);
                m_initialExperienceIntroController.InsertReplayExitIUXChangedCallback(m_onReplayTutorialsModelChanged);

                m_messageBus.SubscribeUi(m_appModeChangedMessageHandler);
            }
            
            OptionsController::~OptionsController()
            {
                m_messageBus.UnsubscribeUi(m_appModeChangedMessageHandler);

                m_initialExperienceIntroController.RemoveReplayExitIUXChangedCallback(m_onReplayTutorialsModelChanged);
                m_interiorsExplorerController.RemoveReplayTutorialsChangedCallback(m_onReplayTutorialsModelChanged);

                m_viewModel.RemoveCacheClearCeremonyCompletedCallback(m_viewModelCacheClearCeremonyCompleted);
                m_viewModel.RemoveOpenedCallback(m_viewModelOpened);
                m_viewModel.RemoveClosedCallback(m_viewModelClosed);
                
                m_view.RemoveReplayTutorialsToggledCallback(m_replayTutorialsToggled);
                m_view.RemoveClearCacheSelectedCallback(m_viewClearCacheSelected);
                m_view.RemoveCacheEnabledSelectionCallback(m_viewCacheEnabledSelectionChanged);
                m_view.RemoveStreamOverWifiOnlySelectionChangedCallback(m_viewStreamOverWifiOnlySelectionChanged);
                m_view.RemoveCloseSelectedCallback(m_viewCloseSelected);
            }
        }
    }
}
