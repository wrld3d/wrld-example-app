// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "iOSInitialExperienceModule.h"
#include "iOSInitialExperiencePreLoadModel.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        iOSInitialExperienceModule::iOSInitialExperienceModule(PersistentSettings::IPersistentSettingsModel& persistentSettings)
        :InitialExperienceModuleBase(persistentSettings)
        {
            
        }
        
        iOSInitialExperienceModule::~iOSInitialExperienceModule()
        {
            
        }
        
        std::vector<IInitialExperienceStep*> iOSInitialExperienceModule::CreateSteps(WorldAreaLoader::IWorldAreaLoaderModel& worldAreaLoaderModel) const
        {
            std::vector<IInitialExperienceStep*> steps;
            
            IInitialExperienceStep* pWorldAreaLoaderStep = Eegeo_NEW(PreLoad::iOSInitialExperiencePreLoadModel)(worldAreaLoaderModel,
                                                                                                                GetPersistentSettings());
            
            steps.push_back(pWorldAreaLoaderStep);
            
            return steps;
        }
    }
}
