// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Space.h"

namespace ExampleApp
{
    namespace InitialLocation
    {
        namespace SdkModel
        {
            class IInitialLocationModel
            {
            public:
                virtual ~IInitialLocationModel() {}
                
                virtual void SetInterestLocation(const Eegeo::Space::LatLongAltitude& lla) = 0;
                
                virtual Eegeo::Space::LatLongAltitude GetInterestLocation() const = 0;
                
                virtual bool HasPersistedInterestLocation() const = 0;
            };

        }
    }
}