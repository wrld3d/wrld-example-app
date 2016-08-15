// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "iOSInitialExperienceModule.h"
#include "iOSInitialExperiencePreLoadModel.h"
#include "InitialExperienceIntroStep.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        iOSInitialExperienceModule::iOSInitialExperienceModule(const std::shared_ptr<PersistentSettings::IPersistentSettingsModel>& persistentSettings,
                                                               const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus)
            : InitialExperienceModuleBase(persistentSettings)
            , m_messageBus(messageBus)
        {
        }

        iOSInitialExperienceModule::~iOSInitialExperienceModule()
        {
            
        }

        std::vector<SdkModel::IInitialExperienceStep*> iOSInitialExperienceModule::CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel)
        {
            std::vector<SdkModel::IInitialExperienceStep*> steps;

            SdkModel::IInitialExperienceStep* pIntroScreenStep = Eegeo_NEW(SdkModel::InitialExperienceIntroStep)(*m_messageBus, GetPersistentSettings());
            
            steps.push_back(pIntroScreenStep);
            
            SdkModel::IInitialExperienceStep* pWorldAreaLoaderStep = Eegeo_NEW(PreLoad::iOSInitialExperiencePreLoadModel)(worldAreaLoaderModel,
                    GetPersistentSettings());

            steps.push_back(pWorldAreaLoaderStep);
            
            return steps;
        }
    }
}
