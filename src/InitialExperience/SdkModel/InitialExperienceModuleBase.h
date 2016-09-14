// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include "IInitialExperienceModule.h"
#include "InitialExperience.h"
#include "WorldAreaLoader.h"
#include "PersistentSettings.h"
#include "Menu.h"
#include <memory>

namespace ExampleApp
{
    namespace InitialExperience
    {
        namespace SdkModel
        {
            class InitialExperienceModuleBase : public IInitialExperienceModule
            {
                IInitialExperienceModel* m_pInitialExperienceModel;
                IInitialExperienceController* m_pInitialExperienceController;

                const std::shared_ptr<PersistentSettings::IPersistentSettingsModel> m_persistentSettings;
                const std::shared_ptr<WorldAreaLoader::SdkModel::IWorldAreaLoaderModel> m_worldAreaLoaderModel;

            public:
                InitialExperienceModuleBase(const std::shared_ptr<PersistentSettings::IPersistentSettingsModel>& persistentSettings,
                                            const std::shared_ptr<WorldAreaLoader::SdkModel::IWorldAreaLoaderModel>& worldAreaLoaderModel);

                ~InitialExperienceModuleBase();

                void TearDown();
                
                void InitialiseWithApplicationModels();

                IInitialExperienceModel& GetInitialExperienceModel() const;

                IInitialExperienceController& GetInitialExperienceController() const;

            protected:

                PersistentSettings::IPersistentSettingsModel& GetPersistentSettings() const;

                virtual std::vector<IInitialExperienceStep*> CreateSteps(WorldAreaLoader::SdkModel::IWorldAreaLoaderModel &worldAreaLoaderModel)  = 0;
                
            };
        }
    }
}
