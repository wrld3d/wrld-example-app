// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultOnMapFactory.h"
#include "SearchResultOnMapItemModel.h"
#include "SearchResultModel.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace View
        {
            SearchResultOnMapFactory::SearchResultOnMapFactory(ExampleAppMessaging::TMessageBus& messageBus,
                                                               Metrics::IMetricsService& metricsService)
                : m_messageBus(messageBus)
                , m_metricsService(metricsService)
            {

            }

            SearchResultOnMapFactory::~SearchResultOnMapFactory()
            {

            }

            SearchResultOnMapItemModel* SearchResultOnMapFactory::CreateSearchResultOnMapItemModel(Search::SdkModel::SearchResultModel& searchResultModel) const
            {
                return Eegeo_NEW(SearchResultOnMapItemModel(searchResultModel,
                                                            m_messageBus,
                                                            m_metricsService));
            }
        }
    }
}
