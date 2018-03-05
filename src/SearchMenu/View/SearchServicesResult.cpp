// Copyright WRLD Ltd (2018-), All Rights Reserved

#include "SearchServicesResult.h"

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			SearchServicesResult::SearchServicesResult(std::string& name,
													   std::string& description,
													   std::string& iconName)
			: m_name(name)
			, m_description(description)
			, m_iconName(iconName)
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
		}
	}
}
