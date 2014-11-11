// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AndroidNativeState.h"
#include "SearchResultOnMapViewModule.h"
#include "ISearchResultOnMapInFocusViewModel.h"
#include "SearchResultOnMapViewController.h"
#include "AndroidAppThreadAssertionMacros.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        SearchResultOnMapViewModule::SearchResultOnMapViewModule(
			AndroidNativeState& nativeState,
			ISearchResultOnMapInFocusViewModel& searchResultOnMapInFocusViewModel,
			ScreenControlViewModel::IScreenControlViewModel& searchResultOnMapInFocusScreenControlViewModel,
			SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel,
			float pinDiameter
		)
        {
    		ASSERT_UI_THREAD

            m_pSearchResultOnMapViewController = Eegeo_NEW(SearchResultOnMapViewController)(
				nativeState,
				searchResultOnMapInFocusViewModel,
				searchResultOnMapInFocusScreenControlViewModel,
				searchResultPoiViewModel,
				pinDiameter
            );
        }
        
        SearchResultOnMapViewModule::~SearchResultOnMapViewModule()
        {
    		ASSERT_UI_THREAD

            Eegeo_DELETE m_pSearchResultOnMapViewController;
        }
        
        SearchResultOnMapViewController& SearchResultOnMapViewModule::GetSearchResultOnMapViewController() const
        {
    		ASSERT_UI_THREAD

            return *m_pSearchResultOnMapViewController;
        }
    }
}
