// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "VectorMathDecl.h"

namespace ExampleApp
{
    namespace CameraTransitions
    {
        class ICameraTransitionController
        {
        public:
            
            virtual ~ICameraTransitionController() {};
            
            virtual void StartTransitionTo(Eegeo::dv3 newInterestPoint, double distanceFromInterest, bool jumpIfFar=true) = 0;
            virtual void StartTransitionTo(Eegeo::dv3 newInterestPoint, double distanceFromInterest, float newHeadingRadians, bool jumpIfFar=true) = 0;
            virtual void StopCurrentTransition() = 0;
            virtual void Update(float dt) = 0;
            
            virtual const bool IsTransitioning() const = 0;
        };
    }
}
