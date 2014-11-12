// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Search.h"
#include "ICallback.h"

namespace ExampleApp
{
	namespace SearchResultPoi
	{
		class ISearchResultPoiViewModel
		{
		public:
			virtual ~ISearchResultPoiViewModel() { }

			virtual const Search::SearchResultModel& GetSearchResultModel() const = 0;

			virtual bool TryAcquireReactorControl() = 0;

			virtual bool IsOpen() const = 0;

			virtual void Open(Search::SearchResultModel& searchResultModel) = 0;

			virtual void Close() = 0;

			virtual void InsertOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

			virtual void RemoveOpenedCallback(Eegeo::Helpers::ICallback0& openedCallback) = 0;

			virtual void InsertClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;

			virtual void RemoveClosedCallback(Eegeo::Helpers::ICallback0& closedCallback) = 0;
		};
	}
}
