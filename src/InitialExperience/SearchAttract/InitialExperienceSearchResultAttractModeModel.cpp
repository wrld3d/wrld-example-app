// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceSearchResultAttractModeModel.h"

namespace
{
    const std::string InitialExperienceModel_HasCompletedSearchMenuAttractExperience_StartedKey = "InitialExperienceModel_HasCompletedSearchMenuAttractExperience_StartedKey";
    
    const std::string InitialExperienceModel_HasCompletedSearchMenuAttractExperience_CompletedKey = "InitialExperienceModel_HasCompletedSearchMenuAttractExperience_CompletedKey";
    
    bool GetKeyValue(ExampleApp::PersistentSettings::IPersistentSettingsModel& persistentSettings, const std::string& key)
    {
        bool result = false;
        
        if(!persistentSettings.TryGetValue(key, result))
        {
            result = false;
        }
        
        return result;
    }
}

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SearchResultAttractMode
        {
            InitialExperienceSearchResultAttractModeModel::InitialExperienceSearchResultAttractModeModel(PersistentSettings::IPersistentSettingsModel& persistentSettings,
                                                                                                         Menu::View::IMenuViewModel& searchMenuViewModelControl,
                                                                                                         SearchResultMenu::View::ISearchResultMenuViewModel& searchResultMenuViewModel,
                                                                                                         ExampleAppMessaging::TMessageBus& messageBus)
            : m_persistentSettings(persistentSettings)
            , m_searchMenuViewModelControl(searchMenuViewModelControl)
            , m_searchResultMenuViewModel(searchResultMenuViewModel)
            , m_messageBus(messageBus)
            , m_shouldEnd(false)
            , m_finished(false)
            , m_onOpenableStateChanged(this, &InitialExperienceSearchResultAttractModeModel::OnSearchResultMenuOpenStateChange)
            , m_onNativeStateEntered(this, &InitialExperienceSearchResultAttractModeModel::OnNativeStateEntered)
            , m_onNativeStateUpdated(this, &InitialExperienceSearchResultAttractModeModel::OnNativeStateUpdated)
            , m_onUiStateExitConditionsMet(this, &InitialExperienceSearchResultAttractModeModel::OnUiStateExitConditionsMet)
            {
                m_messageBus.SubscribeUi(m_onNativeStateEntered);
                m_messageBus.SubscribeUi(m_onNativeStateUpdated);
                m_messageBus.SubscribeNative(m_onUiStateExitConditionsMet);
            }
            
            InitialExperienceSearchResultAttractModeModel::~InitialExperienceSearchResultAttractModeModel()
            {
                m_messageBus.UnsubscribeNative(m_onUiStateExitConditionsMet);
                m_messageBus.UnsubscribeUi(m_onNativeStateUpdated);
                m_messageBus.UnsubscribeUi(m_onNativeStateEntered);
            }
            
            bool InitialExperienceSearchResultAttractModeModel::HasStarted() const
            {
                return true;//GetKeyValue(m_persistentSettings, InitialExperienceModel_HasCompletedSearchMenuAttractExperience_StartedKey);
            }
            
            bool InitialExperienceSearchResultAttractModeModel::HasCompleted() const
            {
                return false;//GetKeyValue(m_persistentSettings, InitialExperienceModel_HasCompletedSearchMenuAttractExperience_CompletedKey);
            }
            
            void InitialExperienceSearchResultAttractModeModel::PerformInitialExperience()
            {
                Eegeo_ASSERT(!HasCompleted(),
                             "Cannot perform InitialExperienceSearchResultAttractModeModel step, has already completed.\n");
                
                m_persistentSettings.SetValue(InitialExperienceModel_HasCompletedSearchMenuAttractExperience_StartedKey, true);
                
                m_messageBus.Publish(InitialExperienceSearchResultAttractModeModelStateEnteredMessage());
            }
            
            void InitialExperienceSearchResultAttractModeModel::EndInitialExperience()
            {
                Eegeo_ASSERT(!HasCompleted(),
                             "Cannot complete InitialExperienceSearchResultAttractModeModel step, has already completed.\n");
                
                m_persistentSettings.SetValue(InitialExperienceModel_HasCompletedSearchMenuAttractExperience_CompletedKey, true);
            }
            
            void InitialExperienceSearchResultAttractModeModel::Update(float deltaSeconds)
            {
                m_messageBus.Publish(InitialExperienceSearchResultAttractModeModelStateUpdatedMessage());
            }
            
            void InitialExperienceSearchResultAttractModeModel::EnterInitialExperienceUi()
            {
                m_searchMenuViewModelControl.InsertOpenStateChangedCallback(m_onOpenableStateChanged);
                
                SetAttractStateBaseOnInteractivity();
            }
            
            void InitialExperienceSearchResultAttractModeModel::ExitInitialExperienceUi()
            {
                m_searchResultMenuViewModel.ExitAttractMode();
                
                m_searchMenuViewModelControl.RemoveOpenStateChangedCallback(m_onOpenableStateChanged);
                
                m_messageBus.Publish(InitialExperienceSearchResultAttractModeModelStateExitedMessage());
                
                m_finished = true;
            }
            
            void InitialExperienceSearchResultAttractModeModel::UpdateUi()
            {
                if(!m_finished)
                {
                    if(m_shouldEnd)
                    {
                        ExitInitialExperienceUi();
                    }
                    else
                    {
                        SetAttractStateBaseOnInteractivity();
                    }
                }
            }
            
            void InitialExperienceSearchResultAttractModeModel::SetAttractStateBaseOnInteractivity()
            {
                if(m_searchResultMenuViewModel.CanInteract())
                {
                    m_searchResultMenuViewModel.EnterAttractMode();
                }
                else
                {
                    m_searchResultMenuViewModel.ExitAttractMode();
                }
            }
            
            void InitialExperienceSearchResultAttractModeModel::OnSearchResultMenuOpenStateChange(OpenableControl::View::IOpenableControlViewModel& viewModel, float& openState)
            {
                if(m_searchMenuViewModelControl.IsFullyOpen())
                {
                    m_shouldEnd = true;
                }
            }
            
            void InitialExperienceSearchResultAttractModeModel::OnNativeStateEntered(const InitialExperienceSearchResultAttractModeModelStateEnteredMessage& message)
            {
                EnterInitialExperienceUi();
            }
            
            void InitialExperienceSearchResultAttractModeModel::OnNativeStateUpdated(const InitialExperienceSearchResultAttractModeModelStateUpdatedMessage& message)
            {
                UpdateUi();
            }
            
            void InitialExperienceSearchResultAttractModeModel::OnUiStateExitConditionsMet(const InitialExperienceSearchResultAttractModeModelStateExitedMessage& message)
            {
                EndInitialExperience();
            }
        }
    }
}