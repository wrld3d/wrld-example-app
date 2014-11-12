// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "SearchResultModel.h"

namespace ExampleApp
{
	namespace SearchResultMenu
	{
		class SearchResultRemovedMessage
		{
			Search::SearchResultModel m_model;

		public:
			SearchResultRemovedMessage(
			    const Search::SearchResultModel& model
			)
				: m_model(model)
			{
			}

			const Search::SearchResultModel& Model() const
			{
				return m_model;
			}
		};
	}
}
