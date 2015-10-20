// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "AppCamera.h"
#include "Camera.h"
#include "GlobeCamera.h"
#include "ITouchController.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            class IAppCameraController : private Eegeo::NonCopyable
            {
            public:
                
                virtual ~IAppCameraController() {}
                
                virtual int CreateCameraHandleFromController(IAppCamera& cameraController) = 0;
                
                virtual void RemoveCameraHandle(int cameraHandle) = 0;
                
                virtual void TransitionToCameraWithHandle(int cameraHandle) = 0;
                
                virtual const bool IsTransitionInFlight() const = 0;
                
                virtual const Eegeo::Camera::CameraState GetCameraState() = 0;
                
                virtual const Eegeo::Camera::RenderCamera& GetRenderCamera() = 0;
                
                virtual Eegeo::ITouchController& GetTouchController() = 0;
                
                virtual void Update(float dt) = 0;
            };
        }
    }
}