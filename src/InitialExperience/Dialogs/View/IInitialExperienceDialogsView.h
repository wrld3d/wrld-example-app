// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "InitialExperienceDialogType.h"
#include <string>

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace Dialogs
		{
			namespace View
			{
				class IInitialExperienceDialogsView
				{
				public:
					virtual ~IInitialExperienceDialogsView() {}

					virtual void Open(const InitialExperienceDialogType::Values& dialogType, const std::string& title, const std::string &description) = 0;
					virtual void Close() = 0;
					virtual void SetModalBackground(bool active) = 0;

					virtual void InsertCloseTappedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
					virtual void RemoveCloseTappedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
				};
			}
		}
	}
}
