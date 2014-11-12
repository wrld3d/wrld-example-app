// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "SearchResultPoi.h"
#include "SearchResultPoiViewModule.h"
#include "ISearchResultPoiViewController.h"
#include "ICallback.h"

namespace ExampleApp
{
	namespace SearchResultPoi
	{
		class SearchResultPoiViewController : public ISearchResultPoiViewController, private Eegeo::NonCopyable
		{
			AndroidNativeState& m_nativeState;
			SearchResultPoi::ISearchResultPoiViewModel& m_searchResultPoiViewModel;
			Eegeo::Helpers::ICallback0* m_pSearchResultPoiOpenedCallback;
			Eegeo::Helpers::ICallback0* m_pSearchResultPoiClosedCallback;

			jclass m_uiViewClass;
			jobject m_uiView;

		public:
			SearchResultPoiViewController(
			    AndroidNativeState& nativeState,
			    SearchResultPoi::ISearchResultPoiViewModel& viewModel
			);

			~SearchResultPoiViewController();

			void HandleCloseButtonPressed();

		private:

			void SearchResultPoiOpenedCallback();

			void SearchResultPoiClosedCallback();
		};
	}
}

