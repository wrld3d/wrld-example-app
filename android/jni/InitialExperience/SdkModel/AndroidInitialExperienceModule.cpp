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

            std::vector<IInitialExperienceStep*> AndroidInitialExperienceModule::CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel)
            {
                std::vector<IInitialExperienceStep*> steps;

                IInitialExperienceStep* pIntroStep = Eegeo_NEW(InitialExperienceIntroStep)(m_messageBus, GetPersistentSettings());
                steps.push_back(pIntroStep);

                return steps;
            }
        }
    }
}
