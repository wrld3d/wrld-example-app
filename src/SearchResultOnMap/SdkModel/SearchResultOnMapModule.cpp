// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SearchResultOnMapModule.h"
#include "Search.h"
#include "SearchResultOnMap.h"
#include "SearchResultOnMapFactory.h"
#include "SearchResultOnMapIconCategoryMapper.h"
#include "SearchResultOnMapModel.h"
#include "IIdentity.h"

namespace ExampleApp
{
	namespace SearchResultOnMap
	{
		SearchResultOnMapModule::SearchResultOnMapModule(Search::ISearchResultRepository& searchResultRepository,
                                                         SearchResultPoi::ISearchResultPoiViewModel& searchResultPoiViewModel,
                                                         WorldPins::IWorldPinsService& worldPinsService,
                                                         ExampleAppMessaging::NativeToUiMessageBus& nativeToUiMessageBus)
		{
			m_pSearchResultOnMapIconCategoryMapper = Eegeo_NEW(SearchResultOnMapIconCategoryMapper);

			m_pSearchResultOnMapFactory = Eegeo_NEW(SearchResultOnMapFactory)(nativeToUiMessageBus);

			SearchResultOnMapModel* pSearchResultOnMapModel = Eegeo_NEW(SearchResultOnMapModel)(worldPinsService,
			        *m_pSearchResultOnMapFactory,
			        *m_pSearchResultOnMapIconCategoryMapper,
			        searchResultRepository);

			m_pSearchResultOnMapModel = pSearchResultOnMapModel;

			m_pSearchResultOnMapItemModelSelectedObserver = Eegeo_NEW(SearchResultOnMapItemModelSelectedObserver)(searchResultPoiViewModel,
			        nativeToUiMessageBus);
		}

		SearchResultOnMapModule::~SearchResultOnMapModule()
		{
			Eegeo_DELETE m_pSearchResultOnMapItemModelSelectedObserver;
			Eegeo_DELETE m_pSearchResultOnMapModel;
			Eegeo_DELETE m_pSearchResultOnMapFactory;
			Eegeo_DELETE m_pSearchResultOnMapIconCategoryMapper;
		}

		ISearchResultOnMapModel& SearchResultOnMapModule::GetSearchResultOnMapModel() const
		{
			return *m_pSearchResultOnMapModel;
		}
	}
}
