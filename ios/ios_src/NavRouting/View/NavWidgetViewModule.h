// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "WrldNav/WrldNav.h"
#include "NavRouteDrawingController.h"
#include "INavRoutingServiceController.h"
#include "NavWidgetController.h"
#include "BidirectionalBus.h"
#include "INavWidgetViewModule.h"
#include "INavWidgetViewModel.h"
#include "NavWidgetViewRouteUpdateHandler.h"
#include "NavWidgetViewRouteDrawingHandler.h"


namespace Eegeo
{
    namespace iOS
    {
        class iOSLocationService;
    }
}

namespace ExampleApp
{
    namespace OpenableControl
    {
        namespace View
        {
            class IOpenableControlViewModel;
        }
    }
    namespace SearchResultPoi
    {
        namespace View
        {
            class SearchResultPoiViewInterop;
        }
    }
    namespace NavRouting
    {
        namespace View
        {
            class NavWidgetViewModule: public INavWidgetViewModule, private Eegeo::NonCopyable
            {
            private:
                NavWidgetController* m_pNavWidgetController;
                NavWidgetView* m_pView ;
                
                NavWidgetViewRouteUpdateHandler* m_pNavWidgetViewRouteUpdateHandler;
                NavWidgetViewRouteDrawingHandler* m_pNavWidgetViewRouteDrawingHandler;
                
                WRLDNavModel* m_pNavModel;
            
            public:
                NavWidgetViewModule(Eegeo::iOS::iOSLocationService* iOSLocationService,
                                ExampleApp::OpenableControl::View::IOpenableControlViewModel& openable,
                                INavWidgetViewModel& viewModel,
                                ExampleApp::NavRouting::SdkModel::NavRouteDrawingController& routeDrawingController,
                                ExampleApp::NavRouting::SdkModel::INavRoutingServiceController& routingServiceController,
                                ExampleAppMessaging::TMessageBus& messageBus);
                
                ~NavWidgetViewModule();
                
                UIView& GetNavWidgetView() const;
                NavWidgetController& GetNavWidgetController() const;
                
            
            };
        }
    }
}
