// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultOnMapItemModel.h"
#include "SearchResultModel.h"
#include "ISearchResultPoiViewModel.h"
#include "Logger.h"
#include "SearchResultOnMapItemModelSelectedMessage.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace View
        {
            SearchResultOnMapItemModel::SearchResultOnMapItemModel(const Search::SdkModel::SearchResultModel& searchResultModel,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Metrics::IMetricsService& metricsService)
                : m_searchResultModel(searchResultModel)
                , m_messageBus(messageBus)
                , m_metricsService(metricsService)
            {

            }

            SearchResultOnMapItemModel::~SearchResultOnMapItemModel()
            {

            }

            void SearchResultOnMapItemModel::SelectPin()
            {
                m_metricsService.SetEvent("Pin Selected", "Name", m_searchResultModel.GetTitle().c_str());
                m_messageBus.Publish(SearchResultOnMapItemModelSelectedMessage(m_searchResultModel));
            }
        }
    }
}
