// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            class IInitialExperienceController
            {
            public:
                virtual ~IInitialExperienceController() { }

                virtual void Update(float deltaSeconds) = 0;
            };
        }
    }
}
