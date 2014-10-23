// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "InitialExperience.h"
#include "WorldAreaLoader.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        class IInitialExperienceModule
        {
        public:
            virtual ~IInitialExperienceModule() { }
            
            virtual void InitialiseWithApplicationModels(WorldAreaLoader::IWorldAreaLoaderModel& worldAreaLoaderModel) = 0;
            
            virtual void TearDown() = 0;
            
            virtual IInitialExperienceController& GetInitialExperienceController() const = 0;
            
            virtual IInitialExperienceModel& GetInitialExperienceModel() const = 0;
        };
    }
}
