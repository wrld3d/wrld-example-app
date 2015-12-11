// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "iOSInitialExperienceModule.h"
#include "iOSInitialExperiencePreLoadModel.h"
#include "InitialExperienceIntroStep.h"
#include "InitialExperienceSearchResultAttractModeModel.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        iOSInitialExperienceModule::iOSInitialExperienceModule(PersistentSettings::IPersistentSettingsModel& persistentSettings,
                                                               ExampleAppMessaging::TMessageBus& messageBus)
            : InitialExperienceModuleBase(persistentSettings)
            , m_messageBus(messageBus)
            , m_pInitialExperienceSearchResultAttractModeModule(NULL)
        {
        }

        iOSInitialExperienceModule::~iOSInitialExperienceModule()
        {
            Eegeo_DELETE m_pInitialExperienceSearchResultAttractModeModule;
        }

        std::vector<SdkModel::IInitialExperienceStep*> iOSInitialExperienceModule::CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel,
                                                                                               Menu::View::IMenuViewModel& searchMenuViewModelControl/*,
                                                                                               SearchResultMenu::View::ISearchResultMenuViewModel& searchResultMenuViewModel*/)
        {
            std::vector<SdkModel::IInitialExperienceStep*> steps;

            SdkModel::IInitialExperienceStep* pIntroScreenStep = Eegeo_NEW(SdkModel::InitialExperienceIntroStep)(m_messageBus, GetPersistentSettings());
            steps.push_back(pIntroScreenStep);
            
            SdkModel::IInitialExperienceStep* pWorldAreaLoaderStep = Eegeo_NEW(PreLoad::iOSInitialExperiencePreLoadModel)(worldAreaLoaderModel,
                    GetPersistentSettings());

            steps.push_back(pWorldAreaLoaderStep);
            
            m_pInitialExperienceSearchResultAttractModeModule = Eegeo_NEW(SearchResultAttractMode::InitialExperienceSearchResultAttractModeModule)(GetPersistentSettings(),
                                                                                                                                                     searchMenuViewModelControl,/*searchResultMenuViewModel,*/                   m_messageBus);
            
            steps.push_back(&m_pInitialExperienceSearchResultAttractModeModule->GetInitialExperienceStep());
            
            return steps;
        }
    }
}
