// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "VectorMathDecl.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class IInteriorCameraController
            {
            public:
                
                virtual ~IInteriorCameraController() {}

                virtual void SetInterestLocation(const Eegeo::dv3& interestPointEcef) = 0;
                virtual const Eegeo::dv3& GetInterestLocation() const = 0;
                
                virtual void SetDistanceToInterest(float distanceMeters) = 0;
                virtual const float GetDistanceToInterest() const = 0;
            };
        }
    }
}