// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InitialExperience.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            class IInitialExperienceModel
            {
            public:
                virtual ~IInitialExperienceModel() {}

                virtual bool HasCompletedInitialExperience() const = 0;
                virtual bool HasStartedInitialExperience() const = 0;
                virtual bool HasCompletedCurrentStep() const = 0;

                virtual void DoNextPartOfInitialExperience() = 0;

                virtual void UpdateCurrentStep(float deltaSeconds) = 0;
                
                virtual bool LockedCameraStepsCompleted() const = 0;
            };
        }
    }
}
