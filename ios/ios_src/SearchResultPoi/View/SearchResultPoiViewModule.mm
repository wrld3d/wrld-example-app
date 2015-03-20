// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "SearchResultPoiViewModule.h"
#include "ISearchResultPoiViewModel.h"
#include "SearchResultPoiView.h"
#include "SearchResultPoiController.h"
#include "SearchResultPoiViewContainer.h"
#include "SearchResultPoiViewInterop.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            SearchResultPoiViewModule::SearchResultPoiViewModule(ISearchResultPoiViewModel& searchResultPoiViewModel,
                                                                 ExampleAppMessaging::TMessageBus& messageBus,
                                                                 Metrics::IMetricsService& metricsService)
            {
                m_pView = [[SearchResultPoiViewContainer alloc] initWithoutParams];
                
                m_pController = Eegeo_NEW(SearchResultPoiController)(*[m_pView getInterop],
                                                                     searchResultPoiViewModel,
                                                                     messageBus,
                                                                     metricsService);
            }

            SearchResultPoiViewModule::~SearchResultPoiViewModule()
            {
                Eegeo_DELETE m_pController;
                
                [m_pView release];
            }

            SearchResultPoiController& SearchResultPoiViewModule::GetController() const
            {
                return *m_pController;
            }

            SearchResultPoiViewContainer& SearchResultPoiViewModule::GetView() const
            {
                return *m_pView;
            }
        }
    }
}
