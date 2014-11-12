// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "SearchResultPoi.h"
#include "IOpenableControlViewModel.h"

namespace ExampleApp
{
namespace SearchResultPoi
{
class ISearchResultPoiModule
{
public:
	virtual ~ISearchResultPoiModule() { }

	virtual ISearchResultPoiViewModel& GetSearchResultPoiViewModel() const = 0;

	virtual OpenableControlViewModel::IOpenableControlViewModel& GetObservableOpenableControl() const = 0;
};
}
}
