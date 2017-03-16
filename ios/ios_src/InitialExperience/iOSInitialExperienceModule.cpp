// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "iOSInitialExperienceModule.h"
#include "iOSInitialExperiencePreLoadModel.h"
#include "InitialExperienceIntroStep.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        iOSInitialExperienceModule::iOSInitialExperienceModule(PersistentSettings::IPersistentSettingsModel& persistentSettings,
                                                               ExampleAppMessaging::TMessageBus& messageBus)
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

            SdkModel::IInitialExperienceStep* pIntroScreenStep = Eegeo_NEW(SdkModel::InitialExperienceIntroStep)(m_messageBus, GetPersistentSettings());
            
            steps.push_back(pIntroScreenStep);
            
            return steps;
        }
    }
}
