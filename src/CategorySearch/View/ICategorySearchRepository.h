// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <string>
#include "CategorySearch.h"
#include "CategorySearchModel.h"
#include "Search.h"

namespace ExampleApp
{
	namespace CategorySearch
	{
		class ICategorySearchRepository
		{
		public:
			virtual ~ICategorySearchRepository() { }

			virtual bool TryGetCategorySearchNameByQuery(const std::string& query, std::string& out_name) const = 0;
		};

		std::string GetPresentationStringForQuery(const ICategorySearchRepository& categorySearchRepository, const Search::SearchQuery& query);
	}
}
