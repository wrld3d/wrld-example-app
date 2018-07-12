// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "AndroidNativeState.h"
#include "Types.h"
#include "NavWidgetViewIncludes.h"
#include "INavWidgetViewModule.h"
#include "NavWidgetController.h"
#include "NavWidgetViewModel.h"
#include "ILocationService.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "ICompassView.h"
#include "IInteriorsExplorerView.h"
#include "MyTestSearchProvider.h"
#include "ISearchResultsRepository.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class NavWidgetViewModule: public INavWidgetViewModule, private Eegeo::NonCopyable
            {
            private:
                NavWidgetView* m_pView;
                NavWidgetController* m_pController;

                SearchProviders::MyTestSearchProvider* m_pMyTestSearchProvider;


            public:
                NavWidgetViewModule(
                    AndroidNativeState& nativeState,
                    INavWidgetViewModel& navWidgetViewModel,
                    SearchProviders::MyTestSearchProvider& navSearchProvider,
                    SearchMenu::View::ISearchResultsRepository& searchResultsRepository,
                    Eegeo::Helpers::CallbackCollection1<INavWidgetView::THeight>& navWidgetViewTopHeightChangedCallbacks,
                    Eegeo::Helpers::CallbackCollection1<INavWidgetView::THeight>& navWidgetViewBottomHeightChangedCallbacks,
                    ExampleAppMessaging::TMessageBus& messageBus
                );

                ~NavWidgetViewModule();

                INavWidgetView& GetView() const;
                NavWidgetController& GetController() const;
            };
        }
    }
}
