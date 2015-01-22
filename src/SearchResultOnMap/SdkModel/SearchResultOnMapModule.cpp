// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

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
        namespace SdkModel
        {
            SearchResultOnMapModule::SearchResultOnMapModule(Search::SdkModel::ISearchResultRepository& searchResultRepository,
                    SearchResultPoi::View::ISearchResultPoiViewModel& searchResultPoiViewModel,
                    WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                    ExampleAppMessaging::TMessageBus& messageBus)
            {
                m_pSearchResultOnMapIconCategoryMapper = Eegeo_NEW(View::SearchResultOnMapIconCategoryMapper);

                m_pSearchResultOnMapFactory = Eegeo_NEW(View::SearchResultOnMapFactory)(messageBus);

                SearchResultOnMapModel* pSearchResultOnMapModel = Eegeo_NEW(SearchResultOnMapModel)(worldPinsService,
                        *m_pSearchResultOnMapFactory,
                        *m_pSearchResultOnMapIconCategoryMapper,
                        searchResultRepository);

                m_pSearchResultOnMapModel = pSearchResultOnMapModel;

                m_pSearchResultOnMapItemModelSelectedObserver = Eegeo_NEW(View::SearchResultOnMapItemModelSelectedObserver)(searchResultPoiViewModel,
                        messageBus);
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
}
