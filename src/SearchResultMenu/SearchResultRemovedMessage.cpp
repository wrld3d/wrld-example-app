// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultRemovedMessage.h"

namespace ExampleApp
{
	namespace SearchResultMenu
	{
		SearchResultRemovedMessage::SearchResultRemovedMessage(
			const Search::SearchResultModel& model
		)
			: m_model(model)
		{
		}

		const Search::SearchResultModel& SearchResultRemovedMessage::Model() const
		{
			return m_model;
		}
	}
}
