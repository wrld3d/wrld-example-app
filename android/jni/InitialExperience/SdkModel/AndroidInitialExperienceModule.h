// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <jni.h>
#include "AndroidNativeState.h"
#include "InitialExperienceModuleBase.h"
#include "Types.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            class AndroidInitialExperienceModule : public InitialExperienceModuleBase, private Eegeo::NonCopyable
            {
                AndroidNativeState& m_nativeState;

            public:
                AndroidInitialExperienceModule(
                    AndroidNativeState& m_nativeState,
                    PersistentSettings::IPersistentSettingsModel& persistentSettings
                );

                ~AndroidInitialExperienceModule();

            protected:

                std::vector<IInitialExperienceStep*> CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel) const;
            };
        }
    }
}
