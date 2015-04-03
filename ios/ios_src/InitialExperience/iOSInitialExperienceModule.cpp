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
            :InitialExperienceModuleBase(persistentSettings)
            ,m_messageBus(messageBus)
        {

        }

        iOSInitialExperienceModule::~iOSInitialExperienceModule()
        {

        }

        std::vector<SdkModel::IInitialExperienceStep*> iOSInitialExperienceModule::CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel,
                                                                                               Menu::View::IMenuViewModel& searchMenuViewModelControl,
                                                                                               SearchResultMenu::View::ISearchResultMenuViewModel& searchResultMenuViewModel) const
        {
            std::vector<SdkModel::IInitialExperienceStep*> steps;

            SdkModel::IInitialExperienceStep* pWorldAreaLoaderStep = Eegeo_NEW(PreLoad::iOSInitialExperiencePreLoadModel)(worldAreaLoaderModel,
                    GetPersistentSettings());

            steps.push_back(pWorldAreaLoaderStep);
            
            SdkModel::IInitialExperienceStep* pIntroScreenStep = Eegeo_NEW(SdkModel::InitialExperienceIntroStep)(m_messageBus, GetPersistentSettings());
            steps.push_back(pIntroScreenStep);
            
            SdkModel::IInitialExperienceStep* pSearchAttractStep = Eegeo_NEW(SearchResultAttractMode::InitialExperienceSearchResultAttractModeModel)(GetPersistentSettings(),
                                                                                                                                                     searchMenuViewModelControl,searchResultMenuViewModel,                   m_messageBus);
            steps.push_back(pSearchAttractStep);
            
            return steps;
        }
    }
}
