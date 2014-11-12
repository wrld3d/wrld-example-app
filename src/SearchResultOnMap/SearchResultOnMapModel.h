// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <map>
#include "Types.h"
#include "ISearchResultOnMapModel.h"
#include "SearchResultOnMap.h"
#include "Search.h"
#include "WorldPins.h"
#include "ICallback.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		class SearchResultOnMapModel : public ISearchResultOnMapModel, private Eegeo::NonCopyable
		{
		public:
			typedef std::map<Search::SearchResultModel*, ExampleApp::WorldPins::WorldPinItemModel>::iterator mapIt;

		private:
			std::map<Search::SearchResultModel*, ExampleApp::WorldPins::WorldPinItemModel> m_searchResultsToPinModel;

			Search::ISearchResultRepository& m_searchResultRepository;
			ISearchResultOnMapIconCategoryMapper& m_searchResultOnMapIconCategoryMapper;
			ISearchResultOnMapFactory& m_searchResultOnMapFactory;
			WorldPins::IWorldPinsService& m_worldPinsService;
			Eegeo::Helpers::ICallback1<Search::SearchResultModel*>* m_pSearchResultAddedCallback;
			Eegeo::Helpers::ICallback1<Search::SearchResultModel*>* m_pSearchResultRemovedCallback;

		public:
			SearchResultOnMapModel(WorldPins::IWorldPinsService& worldPinsService,
			                       ISearchResultOnMapFactory& searchResultOnMapFactory,
			                       ISearchResultOnMapIconCategoryMapper& searchResultOnMapIconCategoryMapper,
			                       Search::ISearchResultRepository& searchResultRepository);

			~SearchResultOnMapModel();

			mapIt begin();

			mapIt end();

		private:
			void AddSearchResult(Search::SearchResultModel*& pSearchResultModel);

			void RemoveSearchResult(Search::SearchResultModel*& pSearchResultModel);
		};
	}
}
