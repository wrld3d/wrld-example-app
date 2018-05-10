// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetViewModule.h"

#include "WrldNav/WrldNav.h"
#include "WrldNavWidget/WrldNavWidget.h"

#include "SearchResultPoiViewInterop.h"

#include "iOSLocationService.h"

#include "IOpenableControlViewModel.h"

#include "NavWidgetViewRouteUpdateHandler.h"
#include "NavWidgetViewRouteDrawingHandler.h"

#include "BidirectionalBus.h"

#include "NavWidgetView.h"

//Wrld Example App fudges the propagation of touch events so to prevent our touch events getting
//passed down to the Map we need to extend our common widget with a consumesTouch selector.
@interface WRLDNavWidgetBase(ExampleApp)
- (BOOL)consumesTouch:(UITouch *)touch;
@end

@implementation WRLDNavWidgetBase(ExampleApp)
- (BOOL)consumesTouch:(UITouch *)touch
{
    return [self pointInside:[touch locationInView:self] withEvent:nil];
}
@end

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            
            NavWidgetViewModule::NavWidgetViewModule(Eegeo::iOS::iOSLocationService* iOSLocationService,
                                             ExampleApp::OpenableControl::View::IOpenableControlViewModel& openable,
                                             INavWidgetViewModel& viewModel,
                                             ExampleApp::NavRouting::SdkModel::NavRouteDrawingController& routeDrawingController,
                                             ExampleApp::NavRouting::SdkModel::INavRoutingServiceController& routingServiceController,
                                             ExampleAppMessaging::TMessageBus& messageBus_)
            {
                
                m_pNavModel = [[WRLDNavModel alloc] init];
                
                m_pView = Eegeo_NEW(NavWidgetView)(m_pNavModel);
                
                
                
                m_pNavWidgetViewRouteUpdateHandler = Eegeo_NEW(NavWidgetViewRouteUpdateHandler)(m_pNavModel,
                                                                                                routingServiceController);
                
                m_pNavWidgetViewRouteDrawingHandler = [[NavWidgetViewRouteDrawingHandler alloc] initWithDrawingController:(&routeDrawingController) journeyModel:m_pNavModel];
                
                m_pNavWidgetController = Eegeo_NEW(NavWidgetController)(*m_pView,
                                                                        viewModel,
                                                                        *iOSLocationService,
                                                                        messageBus_);
               
                
            }
            
            NavWidgetViewModule::~NavWidgetViewModule()
            {
                delete m_pNavWidgetController;
            }
            
            UIView& NavWidgetViewModule::GetNavWidgetView() const
            {
                return *(m_pView->GetUIView());
            }
            
            NavWidgetController& NavWidgetViewModule::GetNavWidgetController() const
            {
                return *m_pNavWidgetController;
            }
        }
    }
}
