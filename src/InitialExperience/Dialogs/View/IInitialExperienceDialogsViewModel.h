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
				class IInitialExperienceDialogsViewModel
				{
				public:
					virtual ~IInitialExperienceDialogsViewModel() { }

					virtual bool IsOpen() const = 0;

					virtual void Open(const InitialExperienceDialogType::Values& type) = 0;
					virtual void Close() = 0;

					virtual const InitialExperienceDialogType::Values& GetOpenType() const = 0;
					virtual const std::string GetTitle() const = 0;
					virtual const std::string GetDescription() const = 0;

					virtual void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

					virtual void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

					virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

					virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;
				};
			}
		}
	}
}


