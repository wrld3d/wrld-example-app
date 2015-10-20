// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "AppGlobeCameraWrapper.h"
#include "GpsGlobeCameraController.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            AppGlobeCameraWrapper::AppGlobeCameraWrapper(Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& gpsGlobeCameraController)
            : m_gpsGlobeCameraController(gpsGlobeCameraController)
            {
            }
            
            void AppGlobeCameraWrapper::Update(float dt)
            {
                m_gpsGlobeCameraController.Update(dt);
            }
            
            const Eegeo::Camera::CameraState AppGlobeCameraWrapper::GetCameraState() const
            {
                return m_gpsGlobeCameraController.GetCameraState();
            }
            
            const Eegeo::Camera::RenderCamera AppGlobeCameraWrapper::GetRenderCamera() const
            {
                return m_gpsGlobeCameraController.GetRenderCamera();
            }
            
            Eegeo::ITouchController& AppGlobeCameraWrapper::GetTouchController() const
            {
                return m_gpsGlobeCameraController.GetTouchController();
            }
        }
    }
}