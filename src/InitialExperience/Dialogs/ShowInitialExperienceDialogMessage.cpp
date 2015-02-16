// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ShowInitialExperienceDialogMessage.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace Dialogs
		{
			ShowInitialExperienceDialogMessage::ShowInitialExperienceDialogMessage(const InitialExperienceDialogType::Values& dialogType)
			: m_dialogType(dialogType)
			{
			}

			const InitialExperienceDialogType::Values& ShowInitialExperienceDialogMessage::DialogType() const
			{
				return m_dialogType;
			}
		}
	}
}
