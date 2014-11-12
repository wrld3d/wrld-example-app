// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "InitialExperienceModuleBase.h"
#include "InitialExperience.h"
#include "PersistentSettings.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		class iOSInitialExperienceModule : public InitialExperienceModuleBase, private Eegeo::NonCopyable
		{
		public:
			iOSInitialExperienceModule(PersistentSettings::IPersistentSettingsModel& persistentSettings);

			~iOSInitialExperienceModule();

		protected:

			std::vector<IInitialExperienceStep*> CreateSteps(WorldAreaLoader::IWorldAreaLoaderModel& worldAreaLoaderModel) const;
		};
	}
}
