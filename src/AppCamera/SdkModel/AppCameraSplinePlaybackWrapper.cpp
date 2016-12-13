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
                //return Eegeo::dv3(6007.4875420670542, 4993439.8499200866, 3968674.5000672070);
            }
            
            Eegeo::ITouchController& AppCameraSplinePlaybackWrapper::GetTouchController() const
            {
                return m_touchController;
            }
            
            float AppCameraSplinePlaybackWrapper::GetHeadingDegrees() const
            {
                // FIXME
                //Eegeo::Space::EcefTangentBasis cameraInterestBasis;
                //float headingRadians = Eegeo::Camera::CameraHelpers::GetAbsoluteBearingRadians(m_splinePlaybackController.GetCameraState(),
                //                                                                               m_splinePlaybackController.GetCameraState().ViewMatrix().GetRow(3));
                
                //return Eegeo::Math::Rad2Deg(headingRadians);
                return 0.0f;
            }
        }
    }
}
