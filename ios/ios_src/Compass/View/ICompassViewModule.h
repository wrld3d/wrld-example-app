// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Compass.h"

namespace ExampleApp
{
    namespace Compass
    {
        namespace View
        {
            class ICompassViewModule
            {
            public:

                virtual ~ICompassViewModule() { }

                virtual CompassController& GetCompassController() const = 0;
                virtual CompassView& GetCompassView() const = 0;
            };
        }
    }
}
