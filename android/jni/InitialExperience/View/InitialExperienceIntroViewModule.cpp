// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceIntroViewModule.h"
#include "InitialExperienceIntroView.h"
#include "InitialExperienceIntroController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace View
		{
			void InitialExperienceIntroViewModule::Register(const TContainerBuilder& builder)
			{
				builder->registerType<InitialExperienceIntroView>().as<IInitialExperienceIntroView>().singleInstance();
			}

			void InitialExperienceIntroViewModule::RegisterUiLeaves()
			{
				Eegeo_TTY("InitialExperienceIntroViewModule::RegisterUiLeaves begin");
				ASSERT_UI_THREAD
				RegisterLeaf<IInitialExperienceIntroView>();
				Eegeo_TTY("InitialExperienceIntroViewModule::RegisterUiLeaves end");
			}
		}
	}
}
