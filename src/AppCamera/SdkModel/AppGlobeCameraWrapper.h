// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Camera.h"
#include "GlobeCamera.h"
#include "IAppCamera.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            class AppGlobeCameraWrapper : public IAppCamera
            {
            public:
                
                AppGlobeCameraWrapper(Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& gpsGlobeCameraController);
                
                void Update(float dt);
                
                const Eegeo::Camera::CameraState GetCameraState() const;
                
                const Eegeo::Camera::RenderCamera GetRenderCamera() const;
                
                Eegeo::dv3 ComputeNonFlattenedCameraPosition() const;
                
                Eegeo::ITouchController& GetTouchController() const;
                
                Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& GetGlobeCameraController() const { return m_gpsGlobeCameraController; }
                
                float GetHeadingDegrees() const;
                
            private:
                
                Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_gpsGlobeCameraController;
            };
        }
    }
}