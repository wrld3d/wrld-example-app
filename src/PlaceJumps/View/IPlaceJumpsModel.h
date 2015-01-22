// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Space.h"
#include <string>

namespace ExampleApp
{
    namespace PlaceJumps
    {
        namespace View
        {
            class IPlaceJumpModel
            {
            public:

                virtual ~IPlaceJumpModel() {}

                virtual std::string GetName() const = 0;
                virtual Eegeo::Space::LatLong GetLocation() const = 0;
                virtual float GetHeadingDegrees() const = 0;
                virtual float GetDistance() const = 0;
            };
        }
    }
}
