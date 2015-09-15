// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "GlobeCameraTouchController.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                class IToursCameraModule
                {
                public:
                    
                    virtual ~IToursCameraModule() {}
                    
                    virtual IToursCameraController& GetToursCameraController() const = 0;
                    
                    virtual IToursCameraTransitionController & GetCameraTransitionController() const = 0;
                    
                    virtual Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& GetCameraTouchController() const = 0;
                };
            }
        }
    }
}