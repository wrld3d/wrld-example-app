// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InitialExperienceDialogsViewModel.h"

namespace ExampleApp
{
	namespace InitialExperience
	{
		namespace Dialogs
		{
			namespace View
			{
				InitialExperienceDialogsViewModel::InitialExperienceDialogsViewModel(
					const std::map<InitialExperienceDialogType::Values, std::string>& dialogTypeToTitleMap,
					const std::map<InitialExperienceDialogType::Values, std::string>& dialogTypeToDescriptionMap)
				: m_dialogTypeToTitleMap(dialogTypeToTitleMap)
				, m_dialogTypeToDescriptionMap(dialogTypeToDescriptionMap)
				, m_currentlyOpenDialogType(InitialExperienceDialogType::INVALID)
				, m_opened(false)
				{

				}

				InitialExperienceDialogsViewModel::~InitialExperienceDialogsViewModel()
				{

				}

				bool InitialExperienceDialogsViewModel::IsOpen() const
				{
					return m_opened;
				}

				const InitialExperienceDialogType::Values& InitialExperienceDialogsViewModel::GetOpenType() const
				{
					return m_currentlyOpenDialogType;
				}

				const std::string InitialExperienceDialogsViewModel::GetTitle() const
				{
					Eegeo_ASSERT(m_currentlyOpenDialogType != InitialExperienceDialogType::INVALID, "Cannot get title of invalid dialog type");
					std::map<InitialExperienceDialogType::Values, std::string>::const_iterator it = m_dialogTypeToTitleMap.find(m_currentlyOpenDialogType);
					return it->second;
				}

				const std::string InitialExperienceDialogsViewModel::GetDescription() const
				{
					Eegeo_ASSERT(m_currentlyOpenDialogType != InitialExperienceDialogType::INVALID, "Cannot get description of invalid dialog type");
					std::map<InitialExperienceDialogType::Values, std::string>::const_iterator it = m_dialogTypeToDescriptionMap.find(m_currentlyOpenDialogType);
					return it->second;
				}

				void InitialExperienceDialogsViewModel::Open(const InitialExperienceDialogType::Values& type)
				{
					if(!IsOpen())
					{
						m_opened = true;
						m_currentlyOpenDialogType = type;
						m_openedCallbacks.ExecuteCallbacks();
					}
				}

				void InitialExperienceDialogsViewModel::Close()
				{
					if(IsOpen())
					{
						m_opened = false;
						m_closedCallbacks.ExecuteCallbacks();
						m_currentlyOpenDialogType = InitialExperienceDialogType::INVALID;
					}
				}

				void InitialExperienceDialogsViewModel::InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
				{
					m_openedCallbacks.AddCallback(openedCallback);
				}

				void InitialExperienceDialogsViewModel::RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback)
				{
					m_openedCallbacks.RemoveCallback(openedCallback);
				}

				void InitialExperienceDialogsViewModel::InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
				{
					m_closedCallbacks.AddCallback(closedCallback);
				}

				void InitialExperienceDialogsViewModel::RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback)
				{
					m_closedCallbacks.RemoveCallback(closedCallback);
				}
			}
		}
	}
}
