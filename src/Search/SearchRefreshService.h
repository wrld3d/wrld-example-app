// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "Search.h"
#include "Space.h"
#include "ISearchRefreshService.h"
#include "ICallback.h"
#include "SearchQuery.h"
#include "CameraTransitions.h"
#include "VectorMath.h"

namespace ExampleApp
{
	namespace Search
	{
		class SearchRefreshService : public ISearchRefreshService, private Eegeo::NonCopyable
		{
			const float m_minimumSecondsBetweenUpdates;
			const float m_minimumMetresSquaredBetweenUpdates;

			ISearchService& m_searchService;
			ISearchQueryPerformer& m_searchQueryPerformer;
			CameraTransitions::ICameraTransitionController& m_cameraTransitionsController;
			Eegeo::Helpers::ICallback1<const SearchQuery&>* m_pSearchResultQueryIssuedCallback;
			Eegeo::Helpers::ICallback2<const SearchQuery&, const std::vector<SearchResultModel>&>* m_pSearchResultResponseReceivedCallback;
			Eegeo::Helpers::ICallback0* m_pSearchQueryResultsClearedCallback;
			int m_queriesPending;
			bool m_searchResultsExist;
			float m_secondsSincePreviousRefresh;
			bool m_cameraTransitioning;
			Eegeo::dv3 m_previousQueryLocationEcef;

		public:
			SearchRefreshService(ISearchService& searchService,
			                     ISearchQueryPerformer& searchQueryPerformer,
			                     CameraTransitions::ICameraTransitionController& cameraTransitionsController,
			                     float minimumSecondsBetweenUpdates,
			                     float minimumMetresBetweenUpdates);

			~SearchRefreshService();

			void TryRefreshSearch(float deltaSeconds, const Eegeo::dv3& ecefLocation);

		private:
			void HandleSearchQueryIssued(const SearchQuery& query);

			void HandleSearchResultsResponseReceived(const SearchQuery& query,
			        const std::vector<SearchResultModel>& results);

			void HandleSearchQueryResultsCleared();
		};
	}
}

