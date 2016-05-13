// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "WindowsNativeState.h"
#include "Types.h"
#include "SearchResultPoi.h"
#include "SearchResultPoiViewIncludes.h"
#include "ISearchResultPoiViewModule.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "DesktopSearchResultPoiController.h"
#include "IMyPinCreationInitiationView.h"
#include "InteriorSelectionModel.h"

namespace ExampleApp
{
    namespace SearchResultPoi
    {
        namespace View
        {
            class SearchResultPoiViewModule: public ISearchResultPoiViewModule, private Eegeo::NonCopyable
            {
            private:
                SearchResultPoiView* m_pView;
                DesktopSearchResultPoiController* m_pController;

            public:
                SearchResultPoiViewModule(
                    WindowsNativeState& nativeState,
                    ISearchResultPoiViewModel& searchResultPoiViewModel,
                    SearchMenu::View::ISearchMenuView& searchMenuView,
                    ExampleAppMessaging::TMessageBus& messageBus,
                    Metrics::IMetricsService& metricsService,
                    MyPinCreation::View::IMyPinCreationInitiationView& pinCreationInitiationView,
                    Eegeo::Resources::Interiors::InteriorSelectionModel& interiorsSelectionModel
                );

                ~SearchResultPoiViewModule();

                SearchResultPoiView& GetView() const;
                SearchResultPoiController& GetController() const;
            };
        }
    }
}
