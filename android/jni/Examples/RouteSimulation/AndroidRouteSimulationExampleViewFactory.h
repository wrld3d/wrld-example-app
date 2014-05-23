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
#include "MessageQueue.h"
#include "IAndroidExampleMessage.h"

namespace Examples
{
    class AndroidRouteSimulationExampleViewFactory : public IRouteSimulationExampleViewFactory, private Eegeo::NonCopyable
    {
    	AndroidNativeState& m_nativeState;
    	Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& m_messageQueue;

    public:
    	AndroidRouteSimulationExampleViewFactory(
    			AndroidNativeState& androidNativeState,
    	    	Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue);
        
        virtual ~AndroidRouteSimulationExampleViewFactory();
        
        virtual IRouteSimulationExampleView* CreateRouteSimulationExampleView() const;
    };
}

#endif /* defined(__ExampleApp__iOSRouteSimulationExampleViewFactory__) */
