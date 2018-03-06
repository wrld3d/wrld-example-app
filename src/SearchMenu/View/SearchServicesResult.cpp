// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchServicesResult.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			SearchServicesResult::SearchServicesResult(const std::string& name,
													   const std::string& description,
													   const std::string& iconName,
													   int originalIndex,
													   const TSdkSearchResult& sdkSearchResult)
			: m_name(name)
			, m_description(description)
			, m_iconName(iconName)
			, m_originalIndex(originalIndex)
			, m_sdkSearchResult(sdkSearchResult)
			{
            }

			const std::string& SearchServicesResult::GetName() const
            {
				return m_name;
            }

			const std::string& SearchServicesResult::GetDescription() const
            {
				return m_description;
            }

			const std::string& SearchServicesResult::GetIconName() const
            {
				return m_iconName;
            }

			int SearchServicesResult::GetOriginalIndex() const
			{
				return m_originalIndex;
			}

			const SearchServicesResult::TSdkSearchResult& SearchServicesResult::GetSdkSearchResult() const
			{
				return m_sdkSearchResult;
			}
		}
	}
}
