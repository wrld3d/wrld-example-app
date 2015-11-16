// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "AppGlobeCameraWrapper.h"
#include "GpsGlobeCameraController.h"
#include "GlobeCameraController.h"
#include "CameraHelpers.h"

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
            
            Eegeo::dv3 AppGlobeCameraWrapper::ComputeNonFlattenedCameraPosition() const
            {
                return m_gpsGlobeCameraController.GetGlobeCameraController().ComputeNonFlattenedCameraPosition();
            }
            
            Eegeo::ITouchController& AppGlobeCameraWrapper::GetTouchController() const
            {
                return m_gpsGlobeCameraController.GetTouchController();
            }
            
            float AppGlobeCameraWrapper::GetHeadingDegrees() const
            {
                Eegeo::Space::EcefTangentBasis cameraInterestBasis;
                float headingRadians = Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(m_gpsGlobeCameraController.GetInterestBasis().GetPointEcef(),
                                                                                               m_gpsGlobeCameraController.GetInterestBasis().GetForward());
                
                return Eegeo::Math::Rad2Deg(headingRadians);
            }
        }
    }
}