// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorHeightHelpers.h"

#include "EarthConstants.h"
#include "EcefTangentBasis.h"
#include "InteriorsModel.h"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace InteriorHeightHelpers
        {
            const float INTERIOR_FLOOR_HEIGHT = 5.0f;
            
            float GetFloorHeightAboveSeaLevel(const Eegeo::Resources::Interiors::InteriorsModel& interiorModel, unsigned int floorIndex)
            {
                return static_cast<float>(interiorModel.GetTangentBasis().GetPointEcef().Length() - Eegeo::Space::EarthConstants::Radius) + (floorIndex * INTERIOR_FLOOR_HEIGHT);
            }
        }
    }
}
