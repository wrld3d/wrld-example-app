// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceSearchResultAttractModeModule.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SearchResultAttractMode
        {
            InitialExperienceSearchResultAttractModeModule::InitialExperienceSearchResultAttractModeModule(PersistentSettings::IPersistentSettingsModel& persistentSettings,
                                                                                                           Menu::View::IMenuViewModel& searchMenuViewModelControl,
//                                                                                                           SearchResultMenu::View::ISearchResultMenuViewModel& searchResultMenuViewModel,
                                                                                                           ExampleAppMessaging::TMessageBus& messageBus)
            : m_pInitialExperienceSearchResultAttractModeModel(NULL)
            , m_pInitialExperienceSearchResultAttractModeViewController(NULL)
            {
                
                m_pInitialExperienceSearchResultAttractModeModel = Eegeo_NEW(SdkModel::InitialExperienceSearchResultAttractModeModel)(persistentSettings,
                                                                                                      messageBus);
                
                m_pInitialExperienceSearchResultAttractModeViewController = Eegeo_NEW(View::InitialExperienceSearchResultAttractModeViewController)(searchMenuViewModelControl,
                                                                                                      /*searchResultMenuViewModel,*/                   messageBus);
            }
            
            InitialExperienceSearchResultAttractModeModule::~InitialExperienceSearchResultAttractModeModule()
            {
                Eegeo_DELETE m_pInitialExperienceSearchResultAttractModeViewController;
                Eegeo_DELETE m_pInitialExperienceSearchResultAttractModeModel;
            }
            
            InitialExperience::SdkModel::IInitialExperienceStep& InitialExperienceSearchResultAttractModeModule::GetInitialExperienceStep()
            {
                return *m_pInitialExperienceSearchResultAttractModeModel;
            }
        }
    }
}