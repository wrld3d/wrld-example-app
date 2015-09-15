// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "CameraState.h"
#include "Camera.h"
#include "ScreenProperties.h"
#include "GlobeCameraTouchController.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                class IToursCameraController
                {
                public:
                    virtual ~IToursCameraController() {}
                    
                    virtual void Update(float dt) = 0;
                    
                    virtual void SetMode(IToursCameraMode* pMode) = 0;
                    
                    virtual Eegeo::Camera::CameraState GetCameraState() const = 0;
                    
                    virtual const Eegeo::Camera::RenderCamera& GetRenderCamera() const = 0;
                    
                    virtual Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& GetTouchController() const = 0;
                    
                    virtual void UpdateScreenProperties(const Eegeo::Rendering::ScreenProperties& screenProperties) = 0;
                };
            }
        }
    }
}