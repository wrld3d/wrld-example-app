//
//  EnvironmentFlatteningExample.cpp
//  ExampleApp
//
//  Created by Scott on 04/06/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#include "EnvironmentFlatteningExample.h"
#include "TimeHelpers.h"

using namespace Examples;
using namespace Eegeo::Rendering;
using namespace Eegeo::Helpers::Time;

#define ENVIRONMENT_FLATTEN_DIRECTION_SWITCH_DELAY_MILLISECONDS 5000

EnvironmentFlatteningExample::EnvironmentFlatteningExample(Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService)
:m_environmentFlatteningService(environmentFlatteningService)
,m_lastToggle(MillisecondsSinceEpoch())
,m_scaleUp(true)
,m_initialEnvironmentScale(environmentFlatteningService.GetCurrentScale())
{
}

void EnvironmentFlatteningExample::Suspend()
{
    m_environmentFlatteningService.SetCurrentScale(m_initialEnvironmentScale);
}

void EnvironmentFlatteningExample::Update(float dt)
{
    long long ms = MillisecondsSinceEpoch();
    long long delta = ms - m_lastToggle;
    
    while(delta > ENVIRONMENT_FLATTEN_DIRECTION_SWITCH_DELAY_MILLISECONDS)
    {
        m_lastToggle = ms;
        delta -= ENVIRONMENT_FLATTEN_DIRECTION_SWITCH_DELAY_MILLISECONDS;
        m_scaleUp = !m_scaleUp;
    }
    
    float scale = (float)delta/ENVIRONMENT_FLATTEN_DIRECTION_SWITCH_DELAY_MILLISECONDS;
    
    if(!m_scaleUp) {
        scale = 1.f - scale;
    }
    
    m_environmentFlatteningService.SetCurrentScale(scale);
}