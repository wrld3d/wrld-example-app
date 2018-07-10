// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InteriorsExplorer.h"
#include "InteriorsExplorerViewIncludes.h"
#include "BidirectionalBus.h"
#include "Rendering.h"
#include "MyPinCreation.h"
#include "MyPinCreationDetails.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "IIdentity.h"
#include "Interiors.h"
#include "ScreenControlViewModelIncludes.h"
#include "IInteriorsExplorerViewModule.h"
#include "InteriorsExplorerView.h"
#include "AndroidNativeState.h"
#include "NavigationService.h"
#include "INavWidgetView.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class InteriorsExplorerViewModule : public IInteriorsExplorerViewModule, private Eegeo::NonCopyable
            {
            private:
                InteriorsExplorerController* m_pController;
                InteriorsExplorerView* m_pView;
                InteriorStreamingDialogView* m_pStreamingDialogView;
                
            public:
                InteriorsExplorerViewModule(SdkModel::InteriorsExplorerModel& model,
                							InteriorsExplorerViewModel& viewModel,
                                            ExampleAppMessaging::TMessageBus& messageBus,
											AndroidNativeState &nativeState,
                                            Eegeo::Location::NavigationService& navigationService,
                                            Eegeo::Helpers::CallbackCollection1<NavRouting::View::INavWidgetView::THeight>& navWidgetViewTopHeightChangedCallbacks,
                                            Eegeo::Helpers::CallbackCollection1<NavRouting::View::INavWidgetView::THeight>& navWidgetViewBottomHeightChangedCallbacks);
                
                ~InteriorsExplorerViewModule();
                
                InteriorsExplorerController& GetController() const;
                
                InteriorsExplorerView& GetView() const;
            };
        }
    }
}
