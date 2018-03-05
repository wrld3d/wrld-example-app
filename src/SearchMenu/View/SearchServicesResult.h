// Copyright WRLD Ltd (2018-), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
    namespace SearchMenu
    {
		namespace View
		{
			class SearchServicesResult
			{
			private:
				std::string m_name;
				std::string m_description;
				std::string m_iconName;

			public:
				SearchServicesResult(std::string& name,
									 std::string& description,
									 std::string& iconName);

				const std::string& GetName()        const;
				const std::string& GetDescription() const;
				const std::string& GetIconName()    const;
			};
		}
	}
}
