// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "WrldNav/WrldNav.h"
#include "WrldNavWidget/WrldNavWidget.h"
#include "NavRouteDrawingController.h"
#include "INavRoutingServiceController.h"
#include "NavWidgetController.h"
#include "BidirectionalBus.h"
#include "INavWidgetViewModule.h"
#include "INavWidgetViewModel.h"


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
            class NavWidgetViewModule: public INavWidgetViewModule, public WRLDNavModelObserverCpp , private Eegeo::NonCopyable
            {
            private:
                NavWidgetController* m_pNavWidgetController;
                NavWidgetView* m_pView ;

                WRLDNavModel* m_pNavModel;
            
            public:
                NavWidgetViewModule(Eegeo::iOS::iOSLocationService* iOSLocationService,
                                ExampleApp::OpenableControl::View::IOpenableControlViewModel& openable,
                                INavWidgetViewModel& viewModel,
                                ExampleAppMessaging::TMessageBus& messageBus);
                
                ~NavWidgetViewModule();
                
                UIView& GetNavWidgetView() const;
                NavWidgetController& GetNavWidgetController() const;
                
                void modelSet();
                
                void changeReceived(const std::string& keyPath);
                
                void eventReceived(WRLDNavEvent key);
                
            
            };
        }
    }
}
