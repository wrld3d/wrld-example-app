//
//  AndroidRouteSimulationExampleViewFactory.h
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__AndroidRouteSimulationExampleViewFactory__
#define __ExampleApp__AndroidRouteSimulationExampleViewFactory__

#include "Types.h"
#include "IRouteSimulationExampleViewFactory.h"
#include "AndroidNativeState.h"
#include "UiThreadToNativeThreadTaskQueue.h"

namespace Examples
{
    class AndroidRouteSimulationExampleViewFactory : public IRouteSimulationExampleViewFactory, private Eegeo::NonCopyable
    {
    	AndroidNativeState& m_nativeState;
    	UiThreadToNativeThreadTaskQueue& m_uiToNativeQueue;

    public:
    	AndroidRouteSimulationExampleViewFactory(AndroidNativeState& androidNativeState, UiThreadToNativeThreadTaskQueue& uiToNativeQueue);
        
        virtual ~AndroidRouteSimulationExampleViewFactory();
        
        virtual IRouteSimulationExampleView* CreateRouteSimulationExampleView() const;
    };
}

#endif /* defined(__ExampleApp__iOSRouteSimulationExampleViewFactory__) */
