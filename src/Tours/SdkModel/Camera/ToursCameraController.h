// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "RenderCamera.h"
#include "Streaming.h"
#include "CameraState.h"
#include "Rendering.h"
#include "Tours.h"
#include "GlobeCamera.h"
#include "ToursCameraState.h"
#include "IToursCameraController.h"
#include "Types.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                class ToursCameraController : public IToursCameraController, private Eegeo::NonCopyable
                {
                public:
                    
                    ToursCameraController(const Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                          Eegeo::Camera::GlobeCamera::GlobeCameraTouchController* pTouchController,
                                          const Eegeo::Rendering::ScreenProperties& screenProperties);
                    
                    void Update(float dt);
                    
                    void SetMode(IToursCameraMode* pMode);
                    
                    Eegeo::Camera::CameraState GetCameraState() const;
                    const Eegeo::Camera::RenderCamera& GetRenderCamera() const { return m_camera; }
                    
                    // todo extract type or common?
                    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& GetTouchController() const { return *m_pTouchController; }
                    
                    void UpdateScreenProperties(const Eegeo::Rendering::ScreenProperties& screenProperties);
                    
                private:
                    
                    Eegeo::Camera::RenderCamera m_camera;
                    const Eegeo::Streaming::ResourceCeilingProvider& m_resourceCeilingProvider;
                    
                    void UpdateCamera();
                    void UpdateFovAndClippingPlanes();
                    
                    IToursCameraMode* m_pCurrentMode;
                    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController* m_pTouchController;

                };
            }
        }
    }
}