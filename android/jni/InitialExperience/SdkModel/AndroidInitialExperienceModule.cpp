// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidInitialExperienceModule.h"
#include "AndroidInitialExperiencePreLoadModel.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            AndroidInitialExperienceModule::AndroidInitialExperienceModule(
                AndroidNativeState& nativeState,
                PersistentSettings::IPersistentSettingsModel& persistentSettings
            )
                : InitialExperienceModuleBase(persistentSettings)
                , m_nativeState(nativeState)
            {

            }

            AndroidInitialExperienceModule::~AndroidInitialExperienceModule()
            {

            }

            std::vector<IInitialExperienceStep*> AndroidInitialExperienceModule::CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel) const
            {
                std::vector<IInitialExperienceStep*> steps;

                IInitialExperienceStep* pWorldAreaLoaderStep = Eegeo_NEW(PreLoad::SdkModel::AndroidInitialExperiencePreLoadModel)(
                            m_nativeState,
                            worldAreaLoaderModel,
                            GetPersistentSettings()
                        );

                steps.push_back(pWorldAreaLoaderStep);

                return steps;
            }
        }
    }
}
