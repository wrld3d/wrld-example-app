// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "InitialExperiencePreLoadModelBase.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace PreLoad
		{
			class iOSInitialExperiencePreLoadModel : public InitialExperiencePreLoadModelBase
			{
				void* m_pAlertListener;

				void DestroyAlertListener();

			public:
				iOSInitialExperiencePreLoadModel(WorldAreaLoader::IWorldAreaLoaderModel& worldAreaLoaderModel,
				                                 PersistentSettings::IPersistentSettingsModel& persistentSettings);

				~iOSInitialExperiencePreLoadModel();

				void HandleDismiss(bool shouldPreload);

			protected:

				void ShowOptions();
			};
		}
	}
}