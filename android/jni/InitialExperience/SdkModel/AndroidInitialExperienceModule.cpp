// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidInitialExperienceModule.h"
#include "AndroidInitialExperiencePreLoadModel.h"
#include "InitialExperienceIntroStep.h"
#include "InitialExperienceSearchResultAttractModeModel.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            AndroidInitialExperienceModule::AndroidInitialExperienceModule(
                AndroidNativeState& nativeState,
                PersistentSettings::IPersistentSettingsModel& persistentSettings,
                ExampleAppMessaging::TMessageBus& messageBus
            )
                : InitialExperienceModuleBase(persistentSettings)
                , m_nativeState(nativeState)
            	, m_messageBus(messageBus)
            {

            }

            AndroidInitialExperienceModule::~AndroidInitialExperienceModule()
            {

            }

            std::vector<IInitialExperienceStep*> AndroidInitialExperienceModule::CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel,
                    Menu::View::IMenuViewModel& searchMenuViewModelControl,
                    SearchResultMenu::View::ISearchResultMenuViewModel& searchResultMenuViewModel) const
            {
                std::vector<IInitialExperienceStep*> steps;

                IInitialExperienceStep* pWorldAreaLoaderStep = Eegeo_NEW(PreLoad::SdkModel::AndroidInitialExperiencePreLoadModel)(
                            m_nativeState,
                            worldAreaLoaderModel,
                            GetPersistentSettings()
                        );

                steps.push_back(pWorldAreaLoaderStep);

                IInitialExperienceStep* pIntroStep = Eegeo_NEW(InitialExperienceIntroStep)(m_messageBus, GetPersistentSettings());
                steps.push_back(pIntroStep);

                SdkModel::IInitialExperienceStep* pSearchAttractStep = Eegeo_NEW(SearchResultAttractMode::InitialExperienceSearchResultAttractModeModel)(GetPersistentSettings(),
                                                                                                                                         searchMenuViewModelControl,
                                                                                                                                         searchResultMenuViewModel,
                                                                                                                                         m_messageBus);

                steps.push_back(pSearchAttractStep);

                return steps;
            }
        }
    }
}
