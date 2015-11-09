// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WindowsInitialExperienceModule.h"
#include "WindowsInitialExperiencePreLoadModel.h"
#include "InitialExperienceIntroStep.h"
#include "InitialExperienceSearchResultAttractModeModel.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            WindowsInitialExperienceModule::WindowsInitialExperienceModule(
                WindowsNativeState& nativeState,
                PersistentSettings::IPersistentSettingsModel& persistentSettings,
                ExampleAppMessaging::TMessageBus& messageBus
            )
                : InitialExperienceModuleBase(persistentSettings)
                , m_nativeState(nativeState)
                , m_messageBus(messageBus)
                , m_pInitialExperienceSearchResultAttractModeModule(NULL)
            {

            }

            WindowsInitialExperienceModule::~WindowsInitialExperienceModule()
            {
                Eegeo_DELETE m_pInitialExperienceSearchResultAttractModeModule;
            }

            std::vector<IInitialExperienceStep*> WindowsInitialExperienceModule::CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel,
                    Menu::View::IMenuViewModel& searchMenuViewModelControl,
                    SearchResultMenu::View::ISearchResultMenuViewModel& searchResultMenuViewModel)
            {
                std::vector<IInitialExperienceStep*> steps;

                IInitialExperienceStep* pIntroStep = Eegeo_NEW(InitialExperienceIntroStep)(m_messageBus, GetPersistentSettings());
                steps.push_back(pIntroStep);

                IInitialExperienceStep* pWorldAreaLoaderStep = Eegeo_NEW(PreLoad::SdkModel::WindowsInitialExperiencePreLoadModel)(
                            m_nativeState,
                            worldAreaLoaderModel,
                            GetPersistentSettings()
                        );

                steps.push_back(pWorldAreaLoaderStep);

                m_pInitialExperienceSearchResultAttractModeModule = Eegeo_NEW(SearchResultAttractMode::InitialExperienceSearchResultAttractModeModule)(GetPersistentSettings(),
                                                                                                                                                         searchMenuViewModelControl,searchResultMenuViewModel,                   m_messageBus);

                steps.push_back(&m_pInitialExperienceSearchResultAttractModeModule->GetInitialExperienceStep());

                return steps;
            }
        }
    }
}
