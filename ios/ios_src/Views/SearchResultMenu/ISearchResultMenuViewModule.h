// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "SearchResultMenuViewIncludes.h"

namespace ExampleApp
{
namespace SearchResultMenu
{
class ISearchResultMenuViewModule
{
public:
	virtual ~ISearchResultMenuViewModule() { }

	virtual MenuViewController& GetSearchResultMenuViewController() const = 0;

	virtual SearchResultMenuView& GetSearchResultMenuView() const = 0;
};
}
}
