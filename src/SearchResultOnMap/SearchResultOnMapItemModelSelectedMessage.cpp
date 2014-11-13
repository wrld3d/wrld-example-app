// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapItemModelSelectedMessage.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
		SearchResultOnMapItemModelSelectedMessage::SearchResultOnMapItemModelSelectedMessage(const Search::SearchResultModel& model)
			: m_model(model)
		{
		}

		const Search::SearchResultModel& SearchResultOnMapItemModelSelectedMessage::GetModel() const
		{
			return m_model;
		}
    }
}
