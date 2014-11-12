// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Search.h"

namespace ExampleApp
{
namespace Search
{
class ISearchModule
{
public:
	virtual ~ISearchModule() { }

	virtual ISearchService& GetSearchService() const = 0;

	virtual ISearchResultRepository& GetSearchResultRepository() const = 0;

	virtual ISearchQueryPerformer& GetSearchQueryPerformer() const = 0;

	virtual ISearchRefreshService& GetSearchRefreshService() const = 0;
};
}
}
