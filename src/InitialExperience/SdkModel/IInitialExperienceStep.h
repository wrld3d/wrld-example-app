// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InitialExperience.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            class IInitialExperienceStep
            {
            public:
                virtual ~IInitialExperienceStep() {}

                virtual bool HasStarted() const = 0;

                virtual bool HasCompleted() const = 0;

                virtual void PerformInitialExperience() = 0;

                virtual void Update(float deltaSeconds) { }
            };
        }
    }
}
