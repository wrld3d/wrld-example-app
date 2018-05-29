// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "NavWidgetViewModule.h"

#include "WrldNav/WrldNav.h"
#include "WrldNavWidget/WrldNavWidget.h"

#include "SearchResultPoiViewInterop.h"

#include "IOpenableControlViewModel.h"

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
            
            NavWidgetViewModule::NavWidgetViewModule(ExampleApp::OpenableControl::View::IOpenableControlViewModel& openable,
                                                     INavWidgetViewModel& viewModel,
                                                     Compass::View::ICompassView& compassView,
                                                     ExampleAppMessaging::TMessageBus& messageBus_)
            {
                registerObserver("selectedDirection");
                
                m_pNavModel = [[WRLDNavModel alloc] init];
                
                setNavModel(m_pNavModel);
                
                m_pView = Eegeo_NEW(NavWidgetView)(m_pNavModel, compassView);
                
                m_pNavWidgetController = Eegeo_NEW(NavWidgetController)(*m_pView,
                                                                        viewModel,
                                                                        messageBus_);
               
            }
            
            NavWidgetViewModule::~NavWidgetViewModule()
            {
                delete m_pNavWidgetController;
                delete m_pView;
            }
            
            UIView& NavWidgetViewModule::GetNavWidgetView() const
            {
                return *(m_pView->GetUIView());
            }
            
            NavWidgetController& NavWidgetViewModule::GetNavWidgetController() const
            {
                return *m_pNavWidgetController;
            }
            
            void NavWidgetViewModule::modelSet()
            {
                
            }
            
            void NavWidgetViewModule::changeReceived(const std::string& keyPath)
            {
                if(keyPath == "selectedDirection")
                {
                    m_pView->HandleSelectedDirectionIndexChangedCallback((int)m_pNavModel.selectedDirection);
                }
            }
            
            void NavWidgetViewModule::eventReceived(WRLDNavEvent key)
            {
                
                switch (key) {
                    case WRLDNavEventCloseSetupJourneyClicked:
                        m_pView->HandleClosedCallback();
                        break;
                    case WRLDNavEventSelectStartLocationClicked:
                        m_pView->HandleStartLocationClickedCallback();
                        break;
                    case WRLDNavEventSelectEndLocationClicked:
                        m_pView->HandleEndLocationClickedCallback();
                        break;
                    case WRLDNavEventStartLocationClearButtonClicked:
                        m_pView->HandleStartLocationClearButtonClickedCallback();
                        break;
                    case WRLDNavEventEndLocationClearButtonClicked:
                        m_pView->HandleEndLocationClearButtonCallback();
                        break;
                    case WRLDNavEventStartEndLocationsSwapped:
                        m_pView->HandleStartEndLocationsSwappedCallback();
                        break;
                    case WRLDNavEventStartEndButtonClicked:
                        m_pView->HandleStartEndRoutingButtonClickedCallback();
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
