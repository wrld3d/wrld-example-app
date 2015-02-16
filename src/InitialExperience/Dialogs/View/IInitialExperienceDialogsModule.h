// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InitialExperienceDialogs.h"

namespace ExampleApp
{
    namespace InitialExperience
    {
		namespace Dialogs
		{
			namespace View
			{
				class IInitialExperienceDialogsModule
	            {
	            public:
	                virtual ~IInitialExperienceDialogsModule() {};

	                virtual IInitialExperienceDialogsViewModel& GetDialogsViewModel() const = 0;
	            };

			}
		}
    }
}
