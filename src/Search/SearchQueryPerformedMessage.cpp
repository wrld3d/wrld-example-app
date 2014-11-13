// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchQueryPerformedMessage.h"

namespace ExampleApp
{
	namespace Search
	{
		SearchQueryPerformedMessage::SearchQueryPerformedMessage(const SearchQuery& searchQuery)
			: m_query(searchQuery)
		{

		}

		const SearchQuery& SearchQueryPerformedMessage::Query() const
		{
			return m_query;
		}
	}
}
