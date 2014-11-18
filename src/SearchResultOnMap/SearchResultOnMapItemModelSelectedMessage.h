// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "SearchResultModel.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class SearchResultOnMapItemModelSelectedMessage
		{
		private:
			Search::SearchResultModel m_model;

		public:
			SearchResultOnMapItemModelSelectedMessage(const Search::SearchResultModel& model);

			const Search::SearchResultModel& GetModel() const;
		};
	}
}
