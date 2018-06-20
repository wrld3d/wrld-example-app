// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "CompassViewIncludes.h"
#include "Rendering.h"
#include "Compass.h"
#include "ICompassViewModule.h"
#include "BidirectionalBus.h"
#include "CompassController.h"
#include "INavWidgetView.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            class CompassViewModule: public ICompassViewModule, private Eegeo::NonCopyable
            {
            private:
                CompassController* m_pController;
                CompassView* m_pView;
                
                Eegeo::Helpers::TCallback1<CompassViewModule, NavRouting::View::INavWidgetView::THeight> m_navWidgetBottomPanelVisibleHeightChangedCallback;
                Eegeo::Helpers::CallbackCollection1<NavRouting::View::INavWidgetView::THeight>& m_navWidgetBottomPanelVisibleHeightChangedCallbacks;
                
                void NavWidgetBottomPanelVisibleHeightChanged(NavRouting::View::INavWidgetView::THeight& newVisibleHeight);

            public:
                CompassViewModule(ICompassViewModel& viewModel,
                                  const Eegeo::Rendering::ScreenProperties& screenProperties,
                                  Eegeo::Helpers::CallbackCollection1<NavRouting::View::INavWidgetView::THeight>& m_navWidgetBottomPanelVisibleHeightChangedCallbacks,
                                  ExampleAppMessaging::TMessageBus& messageBus,
                                  UIViewController* rootViewController);

                ~CompassViewModule();

                CompassController& GetCompassController() const;

                CompassView& GetCompassView() const;
                
                ICompassView& GetCompassViewInterop();
            };
        }
    }
}
