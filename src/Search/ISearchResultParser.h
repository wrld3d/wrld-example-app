// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include <string>
#include "Search.h"

namespace ExampleApp
{
	namespace Search
	{
		class ISearchResultParser
		{
		public:
			virtual ~ISearchResultParser() { }

			virtual void ParseSearchResults(const std::string& serialized,
			                                std::vector<SearchResultModel>& out_results) = 0;
		};
	}
}
