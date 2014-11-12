// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "SearchResultPoi.h"
#include "ISearchResultPoiViewModule.h"

namespace ExampleApp
{
namespace SearchResultPoi
{
class SearchResultPoiViewModule: public ISearchResultPoiViewModule, private Eegeo::NonCopyable
{
private:
	SearchResultPoiViewController* m_pSearchResultPoiViewController;

public:
	SearchResultPoiViewModule(ISearchResultPoiViewModel& searchResultPoiViewModel);

	~SearchResultPoiViewModule();

	SearchResultPoiViewController& GetSearchResultPoiViewController() const;

	SearchResultPoiView& GetSearchResultPoiView() const;
};
}
}
