//
//  ToggleTrafficExample.cpp
//  ExampleApp
//
//  Created by eeGeo on 14/05/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#include "ToggleTrafficExample.h"
#include "TimeHelpers.h"

using namespace Examples;
using namespace Eegeo::Traffic;
using namespace Eegeo::Helpers::Time;

#define TRAFFIC_ENABLED_SWITCH_DELAY_MILLISECONDS 5000

ToggleTrafficExample::ToggleTrafficExample(Eegeo::Traffic::TrafficSimulation& trafficSimulation)
:trafficSimulation(trafficSimulation)
,lastToggle(MillisecondsSinceEpoch())
{
}

void ToggleTrafficExample::Update()
{
    long long ms = MillisecondsSinceEpoch();
    
    if(ms - lastToggle > TRAFFIC_ENABLED_SWITCH_DELAY_MILLISECONDS)
    {
        lastToggle = ms;
        
        Eegeo_TTY("Toggling Traffic - Setting enabled = %s\n", trafficSimulation.Enabled() ? "false!" : "true!");
        trafficSimulation.SetEnabled(!trafficSimulation.Enabled());
    }
}