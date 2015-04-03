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
            namespace SdkModel
            {
                InitialExperienceSearchResultAttractModeModel::InitialExperienceSearchResultAttractModeModel(PersistentSettings::IPersistentSettingsModel& persistentSettings,
                                                                                                             ExampleAppMessaging::TMessageBus& messageBus)
                : m_persistentSettings(persistentSettings)
                , m_messageBus(messageBus)
                , m_onUiStateExitConditionsMet(this, &InitialExperienceSearchResultAttractModeModel::OnUiStateExitConditionsMet)
                {
                    m_messageBus.SubscribeNative(m_onUiStateExitConditionsMet);
                }
                
                InitialExperienceSearchResultAttractModeModel::~InitialExperienceSearchResultAttractModeModel()
                {
                    m_messageBus.UnsubscribeNative(m_onUiStateExitConditionsMet);
                }
                
                bool InitialExperienceSearchResultAttractModeModel::HasStarted() const
                {
                    return GetKeyValue(m_persistentSettings, InitialExperienceModel_HasCompletedSearchMenuAttractExperience_StartedKey);
                }
                
                bool InitialExperienceSearchResultAttractModeModel::HasCompleted() const
                {
                    return GetKeyValue(m_persistentSettings, InitialExperienceModel_HasCompletedSearchMenuAttractExperience_CompletedKey);
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
                
                void InitialExperienceSearchResultAttractModeModel::OnUiStateExitConditionsMet(const InitialExperienceSearchResultAttractModeModelStateExitedMessage& message)
                {
                    EndInitialExperience();
                }
            }
        }
    }
}
