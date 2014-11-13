// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultGainedFocusMessage.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		SearchResultGainedFocusMessage::SearchResultGainedFocusMessage(const Search::SearchResultModel& focussedModel, const Eegeo::v2& screenLocation)
			: m_focussedModel(focussedModel)
			, m_screenLocation(screenLocation)
		{

		}

		const Search::SearchResultModel& SearchResultGainedFocusMessage::FocussedModel() const
		{
			return m_focussedModel;
		}

		const Eegeo::v2& SearchResultGainedFocusMessage::ScreenLocation() const
		{
			return m_screenLocation;
		}
	}
}
