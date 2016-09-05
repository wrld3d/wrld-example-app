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
#include "InteriorSelectionModel.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class DesktopSearchResultPoiController : public SearchResultPoiController
            {
                const std::shared_ptr<MyPinCreation::View::IMyPinCreationInitiationView> m_pinCreationInitiationView;
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorSelectionModel> m_interiorSelectionModel;

                Eegeo::Helpers::TCallback0<DesktopSearchResultPoiController> m_onPinCreationSelected;
                void OnPinCreationSelected();

                Eegeo::Helpers::TCallback1<DesktopSearchResultPoiController, const Eegeo::Resources::Interiors::InteriorId> m_interiorChangedCallback;

                void OnInteriorSelectionChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId);

            public:
                DesktopSearchResultPoiController(
                                                 const std::shared_ptr<ISearchResultPoiView>& view,
                                                 const std::shared_ptr<ISearchResultPoiViewModel>& viewModel,
                                                 const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                                 const std::shared_ptr<Metrics::IMetricsService>& metricsService,
                                                 const std::shared_ptr<MyPinCreation::View::IMyPinCreationInitiationView>& pinCreationInitiationView,
                                                 const std::shared_ptr<Eegeo::Resources::Interiors::InteriorSelectionModel>& interiorSelectionModel);

                virtual ~DesktopSearchResultPoiController();

                void OnViewOpened();
            };
        }
    }
}
