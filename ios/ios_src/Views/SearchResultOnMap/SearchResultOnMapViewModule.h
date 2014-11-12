// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "SearchResultOnMap.h"
#include "ISearchResultOnMapViewModule.h"
#include "IScreenControlViewModel.h"
#include "Modality.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class SearchResultOnMapViewModule: public ISearchResultOnMapViewModule, private Eegeo::NonCopyable
		{
		private:
			SearchResultOnMapViewController* m_pSearchResultOnMapViewController;

		public:
			SearchResultOnMapViewModule(ISearchResultOnMapInFocusViewModel& searchResultOnMapInFocusViewModel,
			                            ScreenControlViewModel::IScreenControlViewModel& searchResultOnMapInFocusScreenControlViewModel,
			                            Modality::IModalityModel& modalityModel,
			                            float pinDiameter,
			                            float pixelScale);

			~SearchResultOnMapViewModule();

			SearchResultOnMapViewController& GetSearchResultOnMapViewController() const;

			SearchResultOnMapView& GetSearchResultOnMapView() const;
		};
	}
}
