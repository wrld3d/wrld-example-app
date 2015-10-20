// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "CameraState.h"
#include "Camera.h"
#include "ScreenProperties.h"
#include "GlobeCameraTouchController.h"
#include "IAppCamera.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                class IToursCameraController : public AppCamera::SdkModel::IAppCamera
                {
                public:
                    virtual ~IToursCameraController() {}
                    
                    virtual void SetMode(IToursCameraMode* pMode) = 0;
                    
                    virtual void UpdateScreenProperties(const Eegeo::Rendering::ScreenProperties& screenProperties) = 0;
                };
            }
        }
    }
}