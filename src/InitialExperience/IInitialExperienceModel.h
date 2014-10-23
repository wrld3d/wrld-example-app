// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "InitialExperience.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        class IInitialExperienceModel
        {
        public:
            virtual ~IInitialExperienceModel() {}
            
            virtual bool HasCompletedInitialExperience() const = 0;
            
            virtual void DoNextPartOfInitialExperience() = 0;
            
            virtual void UpdateCurrentStep(float deltaSeconds) = 0;
        };
    }
}
