// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidNativeState.h"
#include "SearchResultOnMapViewModule.h"
#include "ISearchResultOnMapInFocusViewModel.h"
#include "SearchResultOnMapViewController.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        SearchResultOnMapViewModule::SearchResultOnMapViewModule(
			AndroidNativeState& nativeState,
			ISearchResultOnMapInFocusViewModel& searchResultOnMapInFocusViewModel,
			ScreenControlViewModel::IScreenControlViewModel& searchResultOnMapInFocusScreenControlViewModel,
			Modality::IModalityModel& modalityModel,
			float pinDiameter
		)
        {
            m_pSearchResultOnMapViewController = Eegeo_NEW(SearchResultOnMapViewController)(
				nativeState,
				searchResultOnMapInFocusViewModel,
				searchResultOnMapInFocusScreenControlViewModel,
				modalityModel,
				pinDiameter
            );
        }
        
        SearchResultOnMapViewModule::~SearchResultOnMapViewModule()
        {
            Eegeo_DELETE m_pSearchResultOnMapViewController;
        }
        
        SearchResultOnMapViewController& SearchResultOnMapViewModule::GetSearchResultOnMapViewController() const
        {
            return *m_pSearchResultOnMapViewController;
        }
    }
}
