//
//  AndroidRouteSimulationExampleViewFactory.cpp
//  ExampleApp
//
//  Created by Scott on 19/05/2014.
//  Copyright (c) 2014 eeGeo. All rights reserved.
//

#include "AndroidRouteSimulationExampleViewFactory.h"
#include "AndroidRouteSimulationExampleView.h"

using namespace Examples;

AndroidRouteSimulationExampleViewFactory::AndroidRouteSimulationExampleViewFactory(
		AndroidNativeState& nativeState,
    	Eegeo::Messaging::MessageQueue<IAndroidExampleMessage*>& messageQueue)
: m_nativeState(nativeState)
, m_messageQueue(messageQueue)
{
    
}

AndroidRouteSimulationExampleViewFactory::~AndroidRouteSimulationExampleViewFactory()
{
    
}

IRouteSimulationExampleView* AndroidRouteSimulationExampleViewFactory::CreateRouteSimulationExampleView() const
{
    return Eegeo_NEW(AndroidRouteSimulationExampleView)(m_nativeState, m_messageQueue, false);
}
