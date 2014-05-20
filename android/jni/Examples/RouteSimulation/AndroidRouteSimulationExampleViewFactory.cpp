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

AndroidRouteSimulationExampleViewFactory::AndroidRouteSimulationExampleViewFactory(AndroidNativeState& nativeState, UiThreadToNativeThreadTaskQueue& uiToNativeQueue)
: m_nativeState(nativeState)
, m_uiToNativeQueue(uiToNativeQueue)
{
    
}

AndroidRouteSimulationExampleViewFactory::~AndroidRouteSimulationExampleViewFactory()
{
    
}

IRouteSimulationExampleView* AndroidRouteSimulationExampleViewFactory::CreateRouteSimulationExampleView() const
{
    return Eegeo_NEW(AndroidRouteSimulationExampleView)(m_nativeState, m_uiToNativeQueue, false);
}
