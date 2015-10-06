// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Interiors.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace InteriorHeightHelpers
        {
            extern const float INTERIOR_FLOOR_HEIGHT;
            
            float GetFloorHeightAboveSeaLevel(const Eegeo::Resources::Interiors::InteriorsModel& interiorModel, unsigned int floorIndex);
        }
    }
}
