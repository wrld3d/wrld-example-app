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
#include "IMyPinDetailsViewModel.h"

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

                MyPinDetails::View::IMyPinDetailsViewModel& m_pinDetailsViewModel;

                Eegeo::Helpers::TCallback0<DesktopSearchResultPoiController> m_onPinDetailsOpened;
                void OnPinDetailsOpened();

                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                Eegeo::Helpers::TCallback1<DesktopSearchResultPoiController, const Eegeo::Resources::Interiors::InteriorId> m_interiorChangedCallback;
                Eegeo::Helpers::TCallback1<DesktopSearchResultPoiController, const AppModes::AppModeChangedMessage&> m_appModeChangedHandler;

                void OnInteriorSelectionChanged(const Eegeo::Resources::Interiors::InteriorId& interiorId);

                void OnAppModeChangedMessage(const AppModes::AppModeChangedMessage& message);

            public:
                DesktopSearchResultPoiController(ISearchResultPoiView& view,
                    ISearchResultPoiViewModel& viewModel,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Metrics::IMetricsService& metricsService,
                    MyPinCreation::View::IMyPinCreationInitiationView& pinCreationInitiationView,
                    Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                    MyPinDetails::View::IMyPinDetailsViewModel& pinDetailsViewModel);

                virtual ~DesktopSearchResultPoiController();

                void OnViewOpened();
            };
        }
    }
}
