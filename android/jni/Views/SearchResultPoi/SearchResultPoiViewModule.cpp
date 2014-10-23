// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultPoiViewModule.h"
#include "SearchResultPoi.h"
#include "SearchResultPoiViewController.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        SearchResultPoiViewModule::SearchResultPoiViewModule(
			AndroidNativeState& nativeState,
			SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel
		)
        {
            m_pSearchResultPoiViewController = Eegeo_NEW(SearchResultPoiViewController)(
				nativeState,
				searchResultPoiViewModel
            );
        }
        
        SearchResultPoiViewModule::~SearchResultPoiViewModule()
        {
            Eegeo_DELETE(m_pSearchResultPoiViewController);
        }
        
        ISearchResultPoiViewController& SearchResultPoiViewModule::GetSearchResultPoiViewController() const
        {
            return *m_pSearchResultPoiViewController;
        }
    }
}
