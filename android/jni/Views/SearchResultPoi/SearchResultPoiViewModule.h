// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "SearchResultPoi.h"
#include "SearchResultPoiViewIncludes.h"
#include "ISearchResultPoiViewModule.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        class SearchResultPoiViewModule: public ISearchResultPoiViewModule, private Eegeo::NonCopyable
        {
        private:
        	SearchResultPoi::ISearchResultPoiViewController* m_pSearchResultPoiViewController;

        public:
            SearchResultPoiViewModule(
				AndroidNativeState& nativeState,
				SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel
        	);
            
            ~SearchResultPoiViewModule();
            
            ISearchResultPoiViewController& GetSearchResultPoiViewController() const;
        };
    }
}
