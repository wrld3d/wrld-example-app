// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IInitialExperienceDialogsModule.h"
#include "InitialExperienceDialogs.h"
#include "InitialExperienceDialogsViewModel.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
		namespace Dialogs
		{
			namespace View
			{
				class InitialExperienceDialogsModule : public IInitialExperienceDialogsModule, private Eegeo::NonCopyable
	            {
	            public:
					InitialExperienceDialogsModule();

	                ~InitialExperienceDialogsModule();

	                IInitialExperienceDialogsViewModel& GetDialogsViewModel() const;

	            private:
	                InitialExperienceDialogsViewModel* m_pDialogsViewModel;
	            };

			}
		}
    }
}
