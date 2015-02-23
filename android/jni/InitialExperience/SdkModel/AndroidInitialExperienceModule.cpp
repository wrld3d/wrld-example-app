// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AndroidInitialExperienceModule.h"
#include "AndroidInitialExperiencePreLoadModel.h"
#include "InitialExperienceDialogStep.h"
#include "InitialExperienceDialogType.h"
#include "InitialExperienceDialogStepsFactory.h"

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

            std::vector<IInitialExperienceStep*> AndroidInitialExperienceModule::CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel) const
            {
                std::vector<IInitialExperienceStep*> steps;

                IInitialExperienceStep* pWorldAreaLoaderStep = Eegeo_NEW(PreLoad::SdkModel::AndroidInitialExperiencePreLoadModel)(
                            m_nativeState,
                            worldAreaLoaderModel,
                            GetPersistentSettings()
                        );

                steps.push_back(pWorldAreaLoaderStep);

                Dialogs::SdkModel::InitialExperienceDialogStepsFactory::AddInitialExperienceDialogSteps(m_messageBus, GetPersistentSettings(), steps);

                return steps;
            }
        }
    }
}
