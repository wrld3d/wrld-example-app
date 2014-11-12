// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapViewModule.h"
#include "ISearchResultOnMapInFocusViewModel.h"
#include "SearchResultOnMapViewController.h"
#include "IModalityModel.h"

namespace ExampleApp
{
namespace SearchResultOnMap
{
SearchResultOnMapViewModule::SearchResultOnMapViewModule(ISearchResultOnMapInFocusViewModel& searchResultOnMapInFocusViewModel,
        ScreenControlViewModel::IScreenControlViewModel& searchResultOnMapInFocusScreenControlViewModel,
        Modality::IModalityModel& modalityModel,
        float pinDiameter,
        float pixelScale)
{
	m_pSearchResultOnMapViewController = [[SearchResultOnMapViewController alloc] initWithParams
	                                      :&searchResultOnMapInFocusViewModel
	                                      :&searchResultOnMapInFocusScreenControlViewModel
	                                      :&modalityModel
	                                      :pinDiameter
	                                      :pixelScale];
}

SearchResultOnMapViewModule::~SearchResultOnMapViewModule()
{
	[m_pSearchResultOnMapViewController release];
}

SearchResultOnMapViewController& SearchResultOnMapViewModule::GetSearchResultOnMapViewController() const
{
	return *m_pSearchResultOnMapViewController;
}

SearchResultOnMapView& SearchResultOnMapViewModule::GetSearchResultOnMapView() const
{
	return *[m_pSearchResultOnMapViewController pSearchResultOnMapView];
}
}
}
