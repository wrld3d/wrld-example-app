#pragma once

#import <UIKit/UIKit.h>
#include "NavWidgetViewIncludes.h"
#include "ICallback.h"

namespace ExampleApp
{
    namespace NavRouting
    {
        namespace View
        {
            class NavWidgetLocationSetHandler
            {
            public:
                
                NavWidgetLocationSetHandler(NavWidgetView* pView, NavWidgetSearchController* pSearchController);
                ~NavWidgetLocationSetHandler();
                
            private:
                
                Eegeo::Helpers::TCallback1<NavWidgetLocationSetHandler, const bool> m_locationSetCallback;
                
                void HandleLocationSet(const bool& wasStartLocation);
                
                NavWidgetView* m_pView;
                NavWidgetSearchController* m_pSearchController;
            };
        }
    }
}
            
