// Copyright eeGeo Ltd (2012-2015), All Rights Reserved


#include "AppCameraSplinePlaybackWrapper.h"
#include "CameraSplinePlaybackController.h"
#include "CameraHelpers.h"
#include "GlobeCameraTouchController.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            AppCameraSplinePlaybackWrapper::AppCameraSplinePlaybackWrapper(Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController& splinePlaybackController,
                                                                           Eegeo::ITouchController& touchController)
            : m_splinePlaybackController(splinePlaybackController)
            , m_touchController(touchController)
            {
            }
            
            void AppCameraSplinePlaybackWrapper::Update(float dt)
            {
                m_splinePlaybackController.Update(dt);
            }
            
            const Eegeo::Camera::CameraState AppCameraSplinePlaybackWrapper::GetCameraState() const
            {
                const Eegeo::Camera::CameraState st = m_splinePlaybackController.GetCameraState();
                return st;
            }
            
            const Eegeo::Camera::RenderCamera AppCameraSplinePlaybackWrapper::GetRenderCamera() const
            {
                return m_splinePlaybackController.GetRenderCamera();
            }
            
            Eegeo::dv3 AppCameraSplinePlaybackWrapper::ComputeNonFlattenedCameraPosition() const
            {
                return GetCameraState().LocationEcef();
            }
            
            Eegeo::ITouchController& AppCameraSplinePlaybackWrapper::GetTouchController() const
            {
                return m_touchController;
            }
            
            float AppCameraSplinePlaybackWrapper::GetHeadingDegrees() const
            {
                const Eegeo::m44 view = m_splinePlaybackController.GetCameraState().ViewMatrix();
                const Eegeo::v3 forward = Eegeo::v3(view.GetRow(0).z, view.GetRow(1).z, view.GetRow(2).z).Norm();
                const float headingRadians = Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(m_splinePlaybackController.GetRenderCamera().GetEcefLocation(), forward);
                return Eegeo::Math::Rad2Deg(headingRadians);
            }
        }
    }
}
