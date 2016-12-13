// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Camera.h"
#include "CameraSplinePlaybackController.h"
#include "GlobeCameraTouchController.h"
#include "IAppCamera.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            class AppCameraSplinePlaybackWrapper : public IAppCamera
            {
            public:
                AppCameraSplinePlaybackWrapper(Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController& splinePlaybackController,
                                               Eegeo::ITouchController& touchController);
                
                void Update(float dt);
                
                const Eegeo::Camera::CameraState GetCameraState() const;
                
                const Eegeo::Camera::RenderCamera GetRenderCamera() const;
                
                Eegeo::dv3 ComputeNonFlattenedCameraPosition() const;
                
                Eegeo::ITouchController& GetTouchController() const;
                
                Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController& GetCameraSplinePlaybackController() const
                {
                    return m_splinePlaybackController;
                }
                
                float GetHeadingDegrees() const;
                
            private:
                Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController& m_splinePlaybackController;
                Eegeo::ITouchController& m_touchController;
            };
        }
    }
}
