// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InitialExperienceDialogType.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace Dialogs
		{
			class ShowInitialExperienceDialogMessage
			{
				const InitialExperienceDialogType::Values m_dialogType;

			public:
				ShowInitialExperienceDialogMessage(
					const InitialExperienceDialogType::Values& dialogType
				);

				const InitialExperienceDialogType::Values& DialogType() const;
			};
		}
	}
}
