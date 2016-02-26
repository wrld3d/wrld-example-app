// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InitialExperience.h"
#include "WorldAreaLoader.h"
#include "Menu.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            class IInitialExperienceModule
            {
            public:
                virtual ~IInitialExperienceModule() { }

                virtual void InitialiseWithApplicationModels(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel) = 0;

                virtual void TearDown() = 0;

                virtual IInitialExperienceController& GetInitialExperienceController() const = 0;

                virtual IInitialExperienceModel& GetInitialExperienceModel() const = 0;
            };
        }
    }
}
