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

                    m_view.SetStreamOverWifiOnlySelected(m_viewModel.StreamOverWifiOnly());
                    m_view.SetCacheEnabledSelected      (m_viewModel.CachingEnabled());
                    m_view.SetClearCacheSelected        (false);
                    m_view.SetReplayTutorialsSelected   (false);

                    m_valueOfStreamOverWifiOnly       .Init(m_view.IsStreamOverWifiOnlySelected());
                    m_valueOfCachingEnabled           .Init(m_view.IsCacheEnabledSelected());
                    m_valueOfClearCacheSelected       .Init(false);
                    m_valueOfPlayTutorialAgainSelected.Init(false);
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

            void OptionsController::OnViewOkSelected()
            {
                if (m_viewModel.IsOpen())
                {
                    if (m_valueOfStreamOverWifiOnly.HasChanged())
                    {
                        m_viewModel.SetStreamOverWifiOnly                    (m_valueOfStreamOverWifiOnly.GetValue());
                        m_messageBus.Publish(StreamOverWifiOnlyChangedMessage(m_valueOfStreamOverWifiOnly.GetValue()));
                    }

                    if (m_valueOfCachingEnabled.HasChanged())
                    {
                        m_viewModel.SetCachingEnabled                  (m_valueOfCachingEnabled.GetValue());
                        m_messageBus.Publish(CacheEnabledChangedMessage(m_valueOfCachingEnabled.GetValue()));
                    }

                    if (m_valueOfClearCacheSelected.HasChanged())
                    {
                        if (m_valueOfClearCacheSelected.GetValue())
                            m_view.OpenClearCacheWarning();
                    }

                    if (m_valueOfPlayTutorialAgainSelected.HasChanged())
                    {
                        if (m_valueOfPlayTutorialAgainSelected.GetValue())
                        {
                            m_interiorsExplorerController.ReplayTutorials(true);
                            m_initialExperienceIntroController.ReplayExitIUX(true);
                        }
                    }

                    m_viewModel.Close();
                }
            }
            
            void OptionsController::OnViewStreamOverWifiOnlySelectionChanged()
            {
                m_valueOfStreamOverWifiOnly.SetValue(m_view.IsStreamOverWifiOnlySelected());
            }
            
            void OptionsController::OnViewCacheEnabledSelectionChanged()
            {
                m_valueOfCachingEnabled.SetValue(m_view.IsCacheEnabledSelected());
            }
            
            void OptionsController::OnViewClearCacheSelectionChanged()
            {
				m_valueOfClearCacheSelected.SetValue(m_view.IsClearCacheSelected());
			}

            void OptionsController::OnViewClearCacheTriggered()
            {
                m_viewModel.BeginCacheClearCeremony();

                m_messageBus.Publish(ClearCacheMessage());
            }

            void OptionsController::OnReplayTutorialsToggled(bool& enableTutorials)
            {
                m_valueOfPlayTutorialAgainSelected.SetValue(enableTutorials);
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
                    if(m_tutorialsReplayedCount > 0)
                    {
                        m_view.SetReplayTutorialsSelected(enableTutorials);
                    }
                }
            }

            void OptionsController::OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message)
            {
                const AppModes::SdkModel::AppMode appMode = message.GetAppMode();
                const bool appModeAllowsOpen = appMode != AppModes::SdkModel::AttractMode;

                if (!appModeAllowsOpen)
                {
                    if (m_viewModel.IsOpen())
                    {
                        m_viewModel.Close();
                    }
                }
            }

            void OptionsController::OnDeepLinkOpenedMessage(const DeepLink::DeepLinkOpenedMessage &message)
            {
                m_viewModel.Close();
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
            , m_viewOkSelected(this, &OptionsController::OnViewOkSelected)
            , m_viewStreamOverWifiOnlySelectionChanged(this, &OptionsController::OnViewStreamOverWifiOnlySelectionChanged)
            , m_viewCacheEnabledSelectionChanged(this, &OptionsController::OnViewCacheEnabledSelectionChanged)
            , m_viewClearCacheSelectionChanged(this, &OptionsController::OnViewClearCacheSelectionChanged)
            , m_viewClearCacheTriggered(this, &OptionsController::OnViewClearCacheTriggered)
            , m_replayTutorialsToggled(this, &OptionsController::OnReplayTutorialsToggled)
            , m_onReplayTutorialsModelChanged(this, &OptionsController::OnReplayTutorialsModelChanged)
            , m_appModeChangedHandler(this, &OptionsController::OnAppModeChangedMessage)
            , m_deepLinkOpenedHandler(this, &OptionsController::OnDeepLinkOpenedMessage)
			, m_valueOfStreamOverWifiOnly(false)
			, m_valueOfCachingEnabled(false)
			, m_valueOfClearCacheSelected(false)
			, m_valueOfPlayTutorialAgainSelected(false)
            {
                m_view.InsertCloseSelectedCallback(m_viewCloseSelected);
                m_view.InsertOkSelectedCallback(m_viewOkSelected);
                m_view.InsertStreamOverWifiOnlySelectionChangedCallback(m_viewStreamOverWifiOnlySelectionChanged);
                m_view.InsertCacheEnabledSelectionChangedCallback(m_viewCacheEnabledSelectionChanged);
                m_view.InsertClearCacheSelectionChangedCallback(m_viewClearCacheSelectionChanged);
                m_view.InsertClearCacheTriggeredCallback(m_viewClearCacheTriggered);
                m_view.InsertReplayTutorialsToggledCallback(m_replayTutorialsToggled);

                m_viewModel.InsertClosedCallback(m_viewModelClosed);
                m_viewModel.InsertOpenedCallback(m_viewModelOpened);
                m_viewModel.InsertCacheClearCeremonyCompletedCallback(m_viewModelCacheClearCeremonyCompleted);

                m_interiorsExplorerController.InsertReplayTutorialsChangedCallback(m_onReplayTutorialsModelChanged);
                m_initialExperienceIntroController.InsertReplayExitIUXChangedCallback(m_onReplayTutorialsModelChanged);

                m_messageBus.SubscribeUi(m_appModeChangedHandler);
                m_messageBus.SubscribeUi(m_deepLinkOpenedHandler);
            }
            
            OptionsController::~OptionsController()
            {
                m_messageBus.UnsubscribeUi(m_deepLinkOpenedHandler);
                m_messageBus.UnsubscribeUi(m_appModeChangedHandler);

                m_initialExperienceIntroController.RemoveReplayExitIUXChangedCallback(m_onReplayTutorialsModelChanged);
                m_interiorsExplorerController.RemoveReplayTutorialsChangedCallback(m_onReplayTutorialsModelChanged);

                m_viewModel.RemoveCacheClearCeremonyCompletedCallback(m_viewModelCacheClearCeremonyCompleted);
                m_viewModel.RemoveOpenedCallback(m_viewModelOpened);
                m_viewModel.RemoveClosedCallback(m_viewModelClosed);
                
                m_view.RemoveReplayTutorialsToggledCallback(m_replayTutorialsToggled);
                m_view.RemoveClearCacheTriggeredCallback(m_viewClearCacheTriggered);
                m_view.RemoveClearCacheSelectionChangedCallback(m_viewClearCacheSelectionChanged);
                m_view.RemoveCacheEnabledSelectionChangedCallback(m_viewCacheEnabledSelectionChanged);
                m_view.RemoveStreamOverWifiOnlySelectionChangedCallback(m_viewStreamOverWifiOnlySelectionChanged);
                m_view.RemoveOkSelectedCallback(m_viewOkSelected);
                m_view.RemoveCloseSelectedCallback(m_viewCloseSelected);
            }
        }
    }
}
