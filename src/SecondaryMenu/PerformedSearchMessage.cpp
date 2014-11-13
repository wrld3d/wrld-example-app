// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "PerformedSearchMessage.h"

namespace ExampleApp
{
	namespace SecondaryMenu
	{
		PerformedSearchMessage::PerformedSearchMessage(const std::string& searchQuery, bool isCategory)
			: m_searchQuery(searchQuery)
			, m_isCategory(isCategory)
		{

		}

		const std::string& PerformedSearchMessage::SearchQuery() const
		{
			return m_searchQuery;
		}

		bool PerformedSearchMessage::IsCategory() const
		{
			return m_isCategory;
		}
	}
}
