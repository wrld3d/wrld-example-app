// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "VectorMathDecl.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        namespace SdkModel
        {
            class ICameraTransitionController
            {
            public:

                virtual ~ICameraTransitionController() {};

                virtual void StartTransitionTo(Eegeo::dv3 newInterestPoint, float distanceFromInterest, bool jumpIfFar=true) = 0;
                virtual void StartTransitionTo(Eegeo::dv3 newInterestPoint, float distanceFromInterest, float newHeadingRadians, bool jumpIfFar=true) = 0;
                virtual void StopCurrentTransition() = 0;
                virtual void Update(float dt) = 0;

                virtual const bool IsTransitioning() const = 0;
            };
        }
    }
}
