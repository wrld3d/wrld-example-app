// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                class IToursCameraTransitionController
                {
                public:
                    virtual ~IToursCameraTransitionController() {}
                    
                    virtual bool IsTransitionComplete() const = 0;
                    
                    virtual bool IsTransitioning() const = 0;
                    
                    virtual void Update(float dt) = 0;
                    
                    virtual void SetAppCameraState(ToursCameraState& appCameraState) = 0;
                    
                    virtual void TransitionTo(IToursCameraMode& targetCameraMode) = 0;
                    virtual void TransitionBackToAppCamera(bool returnToOriginalMode) = 0;
                };
            }
        }
    }
}