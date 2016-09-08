// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "DirectionsMenuInitiation.h"
#include "DirectionsMenuInitiationViewIncludes.h"

namespace ExampleApp
{
    namespace DirectionsMenuInitiation
    {
        namespace View
        {
            class IDirectionsMenuInitiationViewModule
            {
            public:

                virtual ~IDirectionsMenuInitiationViewModule() { }

                virtual DirectionsMenuInitiationController& GetDirectionsMenuInitiationController() const = 0;
                virtual DirectionsMenuInitiationView& GetDirectionsMenuInitiationView() const = 0;
            };
        }
    }
}
