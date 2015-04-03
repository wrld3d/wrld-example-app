// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InitialExperience.h"
#include "InitialExperienceIntroViewIncludes.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace View
        {
            class IInitialExperienceIntroViewModule
            {
            public:
                
                virtual ~IInitialExperienceIntroViewModule() { }
                
                virtual InitialExperienceIntroController& GetIntroViewController() const = 0;
                virtual InitialExperienceIntroView& GetIntroView() const = 0;
                virtual InitialExperienceIntroBackgroundView& GetIntroBackgroundView() const = 0;

            };
        }
    }
}