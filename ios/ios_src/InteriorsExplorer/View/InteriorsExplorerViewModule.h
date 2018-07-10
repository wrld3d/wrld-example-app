// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InteriorsExplorer.h"
#include "InteriorsExplorerViewIncludes.h"
#include "BidirectionalBus.h"
#include "MyPinCreationConfirmationViewIncludes.h"
#include "Rendering.h"
#include "MyPinCreation.h"
#include "MyPinCreationDetails.h"
#include "BidirectionalBus.h"
#include "IMetricsService.h"
#include "IIdentity.h"
#include "Interiors.h"
#include "InteriorsExplorerTutorialView.h"
#include "ScreenControlViewModelIncludes.h"
#include "IInteriorsExplorerViewModule.h"
#include "NavigationService.h"
#include "INavWidgetView.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace View
        {
            class InteriorsExplorerViewModule : public IInteriorsExplorerViewModule
            {
            private:
                InteriorsExplorerController* m_pController;
                InteriorsExplorerView* m_pView;
                InteriorsExplorerTutorialView* m_pTutorialView;
                InteriorStreamingDialogView* m_pStreamingDialogView;
                
                Eegeo::Helpers::TCallback1<InteriorsExplorerViewModule, NavRouting::View::INavWidgetView::THeight> m_navWidgetBottomPanelVisibleHeightChangedCallback;
                Eegeo::Helpers::CallbackCollection1<NavRouting::View::INavWidgetView::THeight>& m_navWidgetBottomPanelVisibleHeightChangedCallbacks;
                
                Eegeo::Helpers::TCallback1<InteriorsExplorerViewModule, NavRouting::View::INavWidgetView::THeight> m_navWidgetTopPanelVisibleHeightChangedCallback;
                Eegeo::Helpers::CallbackCollection1<NavRouting::View::INavWidgetView::THeight>& m_navWidgetTopPanelVisibleHeightChangedCallbacks;
                
                void NavWidgetTopPanelVisibleHeightChanged(NavRouting::View::INavWidgetView::THeight& newVisibleHeight);
                void NavWidgetBottomPanelVisibleHeightChanged(NavRouting::View::INavWidgetView::THeight& newVisibleHeight);
                
            public:
                InteriorsExplorerViewModule(SdkModel::InteriorsExplorerModel& model,
                                            InteriorsExplorerViewModel& viewModel,
                                            ExampleAppMessaging::TMessageBus& messageBus,
                                            const Eegeo::Rendering::ScreenProperties& screenProperties,
                                            Eegeo::Helpers::IdentityProvider& identityProvider,
                                            Eegeo::Location::NavigationService& navigationService,
                                            Eegeo::Helpers::CallbackCollection1<NavRouting::View::INavWidgetView::THeight>& m_navWidgetTopPanelVisibleHeightChangedCallbacks,
                                            Eegeo::Helpers::CallbackCollection1<NavRouting::View::INavWidgetView::THeight>& m_navWidgetBottomPanelVisibleHeightChangedCallbacks);
                
                ~InteriorsExplorerViewModule();
                
                InteriorsExplorerController& GetController() const;
                
                InteriorsExplorerView& GetView() const;
                
                InteriorsExplorerTutorialView& GetTutorialView() const;
                
                InteriorStreamingDialogView& GetStreamingDialogView() const;
            };
        }
    }
}
