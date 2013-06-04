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
:environmentFlatteningService(environmentFlatteningService)
,lastToggle(MillisecondsSinceEpoch())
,scaleUp(true)
{
}

void EnvironmentFlatteningExample::Update()
{
    long long ms = MillisecondsSinceEpoch();
    long long delta = ms - lastToggle;
    
    while(delta > ENVIRONMENT_FLATTEN_DIRECTION_SWITCH_DELAY_MILLISECONDS)
    {
        lastToggle = ms;
        delta -= ENVIRONMENT_FLATTEN_DIRECTION_SWITCH_DELAY_MILLISECONDS;
        scaleUp = !scaleUp;
    }
    
    float scale = (float)delta/ENVIRONMENT_FLATTEN_DIRECTION_SWITCH_DELAY_MILLISECONDS;
    
    if(!scaleUp) {
        scale = 1.f - scale;
    }
    
    environmentFlatteningService.SetCurrentScale(scale);
}