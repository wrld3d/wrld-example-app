// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>

namespace ExampleApp
{
	namespace SecondaryMenu
	{
		class PerformedSearchMessage
		{
			std::string m_searchQuery;
			bool m_isCategory;

		public:
			PerformedSearchMessage(const std::string& searchQuery, bool isCategory)
				: m_searchQuery(searchQuery)
				, m_isCategory(isCategory)
			{

			}

			const std::string& SearchQuery() const
			{
				return m_searchQuery;
			}

			bool IsCategory() const
			{
				return m_isCategory;
			}
		};
	}
}
