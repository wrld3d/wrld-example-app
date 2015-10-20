// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Camera.h"
#include "ITouchController.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            class IAppCamera
            {
            public:
                
                virtual ~IAppCamera() {};
                
                virtual void Update(float dt) = 0;
                
                virtual const Eegeo::Camera::CameraState GetCameraState() const = 0;
                
                virtual const Eegeo::Camera::RenderCamera GetRenderCamera() const = 0;
                
                virtual Eegeo::ITouchController& GetTouchController() const = 0;
            };
        }
    }
}