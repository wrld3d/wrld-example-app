// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "VectorMathDecl.h"
#include "Camera.h"
#include "GlobeCamera.h"
#include "Tours.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                class IToursCameraMode
                {
                public:
                    
                    virtual ~IToursCameraMode() {}
                    
                    virtual void UpdateCamera(float dt,
                                              Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                              float inputScreenScale) = 0;
                    
                    virtual const ToursCameraState& GetCurrentState() const = 0;
                    
                    virtual void Reset() = 0;
                };
            }
        }
    }
}