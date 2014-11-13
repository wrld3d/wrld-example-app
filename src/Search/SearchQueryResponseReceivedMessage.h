// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "SearchQuery.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
	namespace Search
	{
		class SearchQueryResponseReceivedMessage
		{
		private:
			const Search::SearchQuery m_query;
			const std::vector<SearchResultModel> m_results;

		public:
			SearchQueryResponseReceivedMessage(const Search::SearchQuery& query,
			                                   const std::vector<SearchResultModel>& results);

			const Search::SearchQuery GetQuery() const;

			const std::vector<SearchResultModel>& GetResults() const;
		};
	}
}
