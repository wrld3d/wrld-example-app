// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

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
			                                   const std::vector<SearchResultModel>& results)
				: m_query(query)
				, m_results(results)
			{
			}

			const Search::SearchQuery GetQuery() const
			{
				return m_query;
			}
			const std::vector<SearchResultModel>& GetResults() const
			{
				return m_results;
			}
		};
	}
}
