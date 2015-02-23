// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "WorldAreaLoader.h"
#include "PersistentSettings.h"
#include "IInitialExperiencePreLoadModel.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace PreLoad
        {
            namespace SdkModel
            {
                class InitialExperiencePreLoadModelBase : public IInitialExperiencePreLoadModel, private Eegeo::NonCopyable
                {
                    WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& m_worldAreaLoaderModel;
                    PersistentSettings::IPersistentSettingsModel& m_persistentSettings;
                    Eegeo::Helpers::ICallback0* m_pPreloadCompleteCallback;

                    void HandlePreloadComplete();

                public:
                    InitialExperiencePreLoadModelBase(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel& worldAreaLoaderModel,
                                                      PersistentSettings::IPersistentSettingsModel& persistentSettings);

                    ~InitialExperiencePreLoadModelBase();

                    bool HasStarted() const;

                    bool HasCompleted() const;

                    void PerformInitialExperience();

                protected:

                    void PrecacheRegion();

                    void Complete();
                };
            }
        }
    }
}
