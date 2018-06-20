// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "CompassViewModule.h"
#include "RenderContext.h"
#include "CompassView.h"
#include "ScreenProperties.h"
#include "CompassViewInterop.h"
#include "INavWidgetView.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            CompassViewModule::CompassViewModule(ICompassViewModel& viewModel,
                                                 const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                 Eegeo::Helpers::CallbackCollection1<NavRouting::View::INavWidgetView::THeight>& m_navWidgetBottomPanelVisibleHeightChangedCallbacks,
                                                 ExampleAppMessaging::TMessageBus& messageBus,
                                                 UIViewController* rootViewController)
            : m_navWidgetBottomPanelVisibleHeightChangedCallback(this, &CompassViewModule::NavWidgetBottomPanelVisibleHeightChanged)
            , m_navWidgetBottomPanelVisibleHeightChangedCallbacks(m_navWidgetBottomPanelVisibleHeightChangedCallbacks)
            {

                m_pView = [[CompassView alloc] initWithParams
                            :screenProperties.GetScreenWidth()
                            :screenProperties.GetScreenHeight()
                            :screenProperties.GetPixelScale()
                            :rootViewController];

                m_pController = Eegeo_NEW(CompassController)(*[m_pView getInterop], viewModel, messageBus);
                
                m_navWidgetBottomPanelVisibleHeightChangedCallbacks.AddCallback(m_navWidgetBottomPanelVisibleHeightChangedCallback);
            }

            CompassViewModule::~CompassViewModule()
            {
                m_navWidgetBottomPanelVisibleHeightChangedCallbacks.RemoveCallback(m_navWidgetBottomPanelVisibleHeightChangedCallback);
                Eegeo_DELETE m_pController;
                [m_pView release];
            }

            CompassController& CompassViewModule::GetCompassController() const
            {
                return *m_pController;
            }

            CompassView& CompassViewModule::GetCompassView() const
            {
                return *m_pView;
            }
            
            ICompassView& CompassViewModule::GetCompassViewInterop()
            {
                return *[m_pView getInterop];
            }
                                                                                
            void CompassViewModule::NavWidgetBottomPanelVisibleHeightChanged(NavRouting::View::INavWidgetView::THeight& newVisibleHeight)
            {
                [m_pView setNavigationModeCompassPosition: newVisibleHeight];
            }
        }
    }
}
