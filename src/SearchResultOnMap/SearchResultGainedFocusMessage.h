// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "SearchResultModel.h"
#include "VectorMath.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class SearchResultGainedFocusMessage
		{
			Search::SearchResultModel m_focussedModel;
			Eegeo::v2 m_screenLocation;

		public:
			SearchResultGainedFocusMessage(const Search::SearchResultModel& focussedModel, const Eegeo::v2& screenLocation);

			const Search::SearchResultModel& FocussedModel() const;

			const Eegeo::v2& ScreenLocation() const;
		};
	}
}
