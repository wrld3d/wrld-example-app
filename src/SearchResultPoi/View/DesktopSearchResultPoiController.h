// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ISearchResultPoiView.h"
#include "ISearchResultPoiViewModel.h"
#include "ICallback.h"
#include "Types.h"
#include "BidirectionalBus.h"
#include "SearchResultModel.h"
#include "IMetricsService.h"
#include "SearchResultPoiController.h"
#include "IMyPinCreationInitiationView.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class DesktopSearchResultPoiController : public SearchResultPoiController
            {
                MyPinCreation::View::IMyPinCreationInitiationView& m_pinCreationInitiationView;

                Eegeo::Helpers::TCallback0<DesktopSearchResultPoiController> m_onPinCreationSelected;

                void OnPinCreationSelected();

            public:
                DesktopSearchResultPoiController(ISearchResultPoiView& view,
                    ISearchResultPoiViewModel& viewModel,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Metrics::IMetricsService& metricsService,
                    MyPinCreation::View::IMyPinCreationInitiationView& pinCreationInitiationView);

                virtual ~DesktopSearchResultPoiController();

                void OnViewOpened();
            };
        }
    }
}
