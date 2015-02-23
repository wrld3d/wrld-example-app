// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IInitialExperienceStep.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace PreLoad
        {
            namespace SdkModel
            {
                class IInitialExperiencePreLoadModel : public InitialExperience::SdkModel::IInitialExperienceStep
                {
                public:
                    virtual ~IInitialExperiencePreLoadModel() { }

                    virtual void ShowOptions() = 0;
                };
            }
        }
    }
}
