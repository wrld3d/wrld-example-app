// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "IInitialExperienceModule.h"
#include "InitialExperience.h"
#include "WorldAreaLoader.h"
#include "PersistentSettings.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		class InitialExperienceModuleBase : public IInitialExperienceModule
		{
			IInitialExperienceModel* m_pInitialExperienceModel;
			IInitialExperienceController* m_pInitialExperienceController;

			PersistentSettings::IPersistentSettingsModel& m_persistentSettings;

		public:
			InitialExperienceModuleBase(PersistentSettings::IPersistentSettingsModel& persistentSettings);

			~InitialExperienceModuleBase();

			void InitialiseWithApplicationModels(WorldAreaLoader::IWorldAreaLoaderModel& worldAreaLoaderModel);

			void TearDown();

			IInitialExperienceModel& GetInitialExperienceModel() const;

			IInitialExperienceController& GetInitialExperienceController() const;

		protected:

			PersistentSettings::IPersistentSettingsModel& GetPersistentSettings() const;

			virtual std::vector<IInitialExperienceStep*> CreateSteps(WorldAreaLoader::IWorldAreaLoaderModel &worldAreaLoaderModel) const = 0;
		};
	}
}
