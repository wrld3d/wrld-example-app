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
			SearchResultGainedFocusMessage(const Search::SearchResultModel& focussedModel, const Eegeo::v2& screenLocation)
			: m_focussedModel(focussedModel)
			, m_screenLocation(screenLocation)
			{

			}

			const Search::SearchResultModel& FocussedModel() const { return m_focussedModel; }

			const Eegeo::v2& ScreenLocation() const { return m_screenLocation; }
		};
	}
}
