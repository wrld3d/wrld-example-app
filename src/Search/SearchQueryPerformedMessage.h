// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "SearchQuery.h"

namespace ExampleApp
{
	namespace Search
	{
		class SearchQueryPerformedMessage
		{
			SearchQuery m_query;

		public:
			SearchQueryPerformedMessage(const SearchQuery& searchQuery)
				: m_query(searchQuery)
			{

			}

			const SearchQuery& Query() const
			{
				return m_query;
			}
		};
	}
}
