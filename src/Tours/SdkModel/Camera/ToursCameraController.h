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
#include "ITouchController.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                class TourGlobeCameraTouchController : public Eegeo::Camera::GlobeCamera::GlobeCameraTouchController
                {
                public:
                    TourGlobeCameraTouchController(Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration config,
                                                   const std::shared_ptr<Eegeo::Rendering::ScreenProperties>& screenProperties)
                    : GlobeCameraTouchController(config, *screenProperties)
                    , m_screenProperties(screenProperties)
                    {
                    }
                private:
                    const std::shared_ptr<Eegeo::Rendering::ScreenProperties> m_screenProperties;
                };
        
                
                class ToursCameraController : public IToursCameraController, private Eegeo::NonCopyable
                {
                public:
                    
                    ToursCameraController(const std::shared_ptr<Eegeo::Streaming::ResourceCeilingProvider>& resourceCeilingProvider,
                                          const std::shared_ptr<TourGlobeCameraTouchController>& touchController,
                                          const std::shared_ptr<Eegeo::Rendering::ScreenProperties>& screenProperties);
                    
                    void Update(float dt);
                    
                    void SetMode(IToursCameraMode* pMode);
                    
                    const Eegeo::Camera::CameraState GetCameraState() const;
                    const Eegeo::Camera::RenderCamera GetRenderCamera() const { return m_camera; }
                    Eegeo::dv3 ComputeNonFlattenedCameraPosition() const { return m_camera.GetEcefLocation(); }
                    
                    Eegeo::ITouchController& GetTouchController() const { return *m_touchController; }
                    
                    void UpdateScreenProperties(const Eegeo::Rendering::ScreenProperties& screenProperties);
                    
                    float GetHeadingDegrees() const;
                    
                private:
                    
                    Eegeo::Camera::RenderCamera m_camera;
                    const std::shared_ptr<const Eegeo::Streaming::ResourceCeilingProvider> m_resourceCeilingProvider;
                    
                    void UpdateCamera();
                    void UpdateFovAndClippingPlanes();
                    
                    IToursCameraMode* m_pCurrentMode;
                    const std::shared_ptr<Eegeo::Camera::GlobeCamera::GlobeCameraTouchController> m_touchController;

                };
            }
        }
    }
}