// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InitialExperienceDialogs.h"
#include "IInitialExperienceDialogsViewModel.h"
#include "InitialExperienceDialogType.h"
#include "ICallback.h"
#include "CallbackCollection.h"
#include <map>

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace Dialogs
		{
			namespace View
			{
				class InitialExperienceDialogsViewModel : public IInitialExperienceDialogsViewModel, private Eegeo::NonCopyable
				{
				public:

					InitialExperienceDialogsViewModel(
							const std::map<InitialExperienceDialogType::Values, std::string>& dialogTypeToTitleMap,
							const std::map<InitialExperienceDialogType::Values, std::string>& dialogTypeToDescriptionMap);

					~InitialExperienceDialogsViewModel();


					bool IsOpen() const;

					void Open(const InitialExperienceDialogType::Values& type);
					void Close();

					const InitialExperienceDialogType::Values& GetOpenType() const;
					const std::string GetTitle() const;
					const std::string GetDescription() const;


					void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);

					void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback);

					void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);

					void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback);

				private:
					Eegeo::Helpers::CallbackCollection0 m_openedCallbacks;
					Eegeo::Helpers::CallbackCollection0 m_closedCallbacks;
					bool m_opened;

					InitialExperienceDialogType::Values m_currentlyOpenDialogType;
					const std::map<InitialExperienceDialogType::Values, std::string> m_dialogTypeToTitleMap;
					const std::map<InitialExperienceDialogType::Values, std::string> m_dialogTypeToDescriptionMap;
				};
			}

		}
	}
}
