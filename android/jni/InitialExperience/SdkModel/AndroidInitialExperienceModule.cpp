// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidInitialExperienceModule.h"
#include "AndroidInitialExperiencePreLoadModel.h"
#include "InitialExperienceIntroStep.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            AndroidInitialExperienceModule::AndroidInitialExperienceModule(
            										   const std::shared_ptr<AndroidNativeState>& nativeState,
                                                       const std::shared_ptr<PersistentSettings::IPersistentSettingsModel>& persistentSettings,
                                                       const std::shared_ptr<WorldAreaLoader::SdkModel::IWorldAreaLoaderModel>& worldAreaLoaderModel,
                                                       const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus
            )
                : InitialExperienceModuleBase(persistentSettings, worldAreaLoaderModel)
                , m_nativeState(nativeState)
            	, m_messageBus(messageBus)
            {

            }

            AndroidInitialExperienceModule::~AndroidInitialExperienceModule()
            {

            }

            std::vector<IInitialExperienceStep*> AndroidInitialExperienceModule::CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel)
            {
                std::vector<IInitialExperienceStep*> steps;

                IInitialExperienceStep* pIntroStep = Eegeo_NEW(InitialExperienceIntroStep)(*m_messageBus, GetPersistentSettings());
                steps.push_back(pIntroStep);

                IInitialExperienceStep* pWorldAreaLoaderStep = Eegeo_NEW(PreLoad::SdkModel::AndroidInitialExperiencePreLoadModel)(
                            *m_nativeState,
                            worldAreaLoaderModel,
                            GetPersistentSettings()
                        );

                steps.push_back(pWorldAreaLoaderStep);

                return steps;
            }
        }
    }
}
