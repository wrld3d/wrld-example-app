// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultPoiViewModule.h"
#include "SearchResultPoi.h"
#include "SearchResultPoiViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
namespace SearchResultPoi
{
SearchResultPoiViewModule::SearchResultPoiViewModule(
    AndroidNativeState& nativeState,
    SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel
)
{
	ASSERT_UI_THREAD

	m_pSearchResultPoiViewController = Eegeo_NEW(SearchResultPoiViewController)(
	                                       nativeState,
	                                       searchResultPoiViewModel
	                                   );
}

SearchResultPoiViewModule::~SearchResultPoiViewModule()
{
	ASSERT_UI_THREAD

	Eegeo_DELETE(m_pSearchResultPoiViewController);
}

ISearchResultPoiViewController& SearchResultPoiViewModule::GetSearchResultPoiViewController() const
{
	ASSERT_UI_THREAD

	return *m_pSearchResultPoiViewController;
}
}
}
