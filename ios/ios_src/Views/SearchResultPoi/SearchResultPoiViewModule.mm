// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultPoiViewModule.h"
#include "ISearchResultPoiViewModel.h"
#include "SearchResultPoiViewController.h"

namespace ExampleApp
{
namespace SearchResultPoi
{
SearchResultPoiViewModule::SearchResultPoiViewModule(ISearchResultPoiViewModel& searchResultPoiViewModel)
{
	m_pSearchResultPoiViewController = [[SearchResultPoiViewController alloc] initWithParams :&searchResultPoiViewModel];
}

SearchResultPoiViewModule::~SearchResultPoiViewModule()
{
	[m_pSearchResultPoiViewController release];
}

SearchResultPoiViewController& SearchResultPoiViewModule::GetSearchResultPoiViewController() const
{
	return *m_pSearchResultPoiViewController;
}

SearchResultPoiView& SearchResultPoiViewModule::GetSearchResultPoiView() const
{
	return *[m_pSearchResultPoiViewController pSearchResultPoiView];
}
}
}
