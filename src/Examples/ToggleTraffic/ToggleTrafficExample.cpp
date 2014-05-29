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

ToggleTrafficExample::ToggleTrafficExample(Eegeo::Traffic::TrafficSimulationController& trafficSimulation)
:m_trafficSimulation(trafficSimulation)
,m_lastToggle(MillisecondsSinceEpoch())
{
}

void ToggleTrafficExample::Suspend()
{
    m_trafficSimulation.SetEnabled(true);
}

void ToggleTrafficExample::Update(float dt)
{
    long long ms = MillisecondsSinceEpoch();
    
    if(ms - m_lastToggle > TRAFFIC_ENABLED_SWITCH_DELAY_MILLISECONDS)
    {
        m_lastToggle = ms;
        
        Eegeo_TTY("Toggling Traffic - Setting enabled = %s\n", m_trafficSimulation.Enabled() ? "false!" : "true!");
        m_trafficSimulation.SetEnabled(!m_trafficSimulation.Enabled());
    }
}