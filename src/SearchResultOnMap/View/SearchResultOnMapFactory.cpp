// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultOnMapFactory.h"
#include "SearchResultOnMapItemModel.h"
#include "SearchResultModel.h"
#include "InteriorsExplorer.h"

namespace ExampleApp
{
    namespace SearchResultOnMap
    {
        namespace View
        {
            SearchResultOnMapFactory::SearchResultOnMapFactory(ExampleAppMessaging::TMessageBus& messageBus,
                                                               Metrics::IMetricsService& metricsService,
                                                               InteriorsExplorer::SdkModel::Highlights::InteriorEntityHighlightController& entityHighlightController)
                : m_messageBus(messageBus)
                , m_metricsService(metricsService)
                , m_entityHighlightController(entityHighlightController)
            {
            }

            SearchResultOnMapFactory::~SearchResultOnMapFactory()
            {

            }

            SearchResultOnMapItemModel* SearchResultOnMapFactory::CreateSearchResultOnMapItemModel(Search::SdkModel::SearchResultModel& searchResultModel) const
            {
                return Eegeo_NEW(SearchResultOnMapItemModel(searchResultModel,
                                                            m_messageBus,
                                                            m_metricsService,
                                                            m_entityHighlightController));
            }
        }
    }
}
