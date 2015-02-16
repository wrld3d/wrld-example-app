// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "iOSInitialExperienceModule.h"
#include "iOSInitialExperiencePreLoadModel.h"
#include "InitialExperienceDialogStepsFactory.h"

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

        std::vector<SdkModel::IInitialExperienceStep*> iOSInitialExperienceModule::CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel) const
        {
            std::vector<SdkModel::IInitialExperienceStep*> steps;

            SdkModel::IInitialExperienceStep* pWorldAreaLoaderStep = Eegeo_NEW(PreLoad::iOSInitialExperiencePreLoadModel)(worldAreaLoaderModel,
                    GetPersistentSettings());

            steps.push_back(pWorldAreaLoaderStep);
            
            Dialogs::SdkModel::InitialExperienceDialogStepsFactory::AddInitialExperienceDialogSteps(m_messageBus, GetPersistentSettings(), steps);

            return steps;
        }
    }
}
