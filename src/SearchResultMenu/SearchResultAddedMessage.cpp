// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultAddedMessage.h"

namespace ExampleApp
{
	namespace SearchResultMenu
	{
		SearchResultAddedMessage::SearchResultAddedMessage(
			const Search::SearchResultModel& model
		)
			: m_model(model)
		{
		}

		const Search::SearchResultModel& SearchResultAddedMessage::Model() const
		{
			return m_model;
		}
	}
}
