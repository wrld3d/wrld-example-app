// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ToursCameraController.h"
#include "MathFunc.h"
#include "ResourceCeilingProvider.h"
#include "SpaceHelpers.h"
#include "CameraHelpers.h"
#include "VectorMath.h"
#include "ScreenProperties.h"
#include "IToursCameraMode.h"
#include "GlobeCameraTouchController.h"
#include "Quaternion.h"
#include "SplineCameraMode.h"


namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                ToursCameraController::ToursCameraController(const Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                                             Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                                             const Eegeo::Rendering::ScreenProperties& screenProperties)
                : m_resourceCeilingProvider(resourceCeilingProvider)
                , m_pCurrentMode(NULL)
                , m_touchController(touchController)
                {
                    UpdateScreenProperties(screenProperties);
                }
                
                void ToursCameraController::SetMode(IToursCameraMode* pMode)
                {
                    m_pCurrentMode = pMode;
                }
                
                void ToursCameraController::Update(float dt)
                {
                    Eegeo_ASSERT(m_pCurrentMode != NULL, "Camera mode is NULL")
                    
                    m_touchController.Update(dt);

                    float screenWidth = m_camera.GetViewportWidth();
                    float screenHeight = m_camera.GetViewportHeight();
                    float inputScreenScale = 1.0f / std::max(screenWidth, screenHeight);
                    m_pCurrentMode->UpdateCamera(dt, m_touchController, inputScreenScale);
                    
                    const ToursCameraState& state = m_pCurrentMode->GetCurrentState();
                    
                    m_camera.SetOrientationMatrix(state.orientationMatrix);
                    m_camera.SetEcefLocation(state.ecefPosition);
                    
                    UpdateFovAndClippingPlanes();
                }
                
                void ToursCameraController::UpdateFovAndClippingPlanes()
                {
                    Eegeo_ASSERT(m_pCurrentMode != NULL, "Camera mode is NULL")
                    
                    float cameraAltitude = static_cast<float>(Eegeo::Space::SpaceHelpers::GetAltitude(m_camera.GetEcefLocation()));
                    float approxTerrainAltitude = m_resourceCeilingProvider.GetApproximateResourceCeilingAltitude();
                    float approxTerrainAltitudeDelta = approxTerrainAltitude - m_resourceCeilingProvider.GetApproximateResourceFloorAltitude();
                    
                    float nearZ;
                    float farZ;
                    const double ClipPlaneThresholdAltitude = 15000.0;
                    Eegeo::Camera::CameraHelpers::GetAltitudeInterpolatedNearFar(
                                                                  cameraAltitude, approxTerrainAltitude, approxTerrainAltitudeDelta, ClipPlaneThresholdAltitude, nearZ, farZ);
                    
                    m_camera.SetProjection(Eegeo::Math::Deg2Rad(m_pCurrentMode->GetCurrentState().fovDegrees), nearZ, farZ);
                }
                
                const Eegeo::Camera::CameraState ToursCameraController::GetCameraState() const
                {
                    Eegeo_ASSERT(m_pCurrentMode != NULL, "Camera mode is NULL")
                    const ToursCameraState& state = m_pCurrentMode->GetCurrentState();
                    return Eegeo::Camera::CameraState(m_camera.GetEcefLocation(),
                                                      state.ecefInterestPoint,
                                                      m_camera.GetViewMatrix(),
                                                      m_camera.GetProjectionMatrix());
                }
                
                
                void ToursCameraController::UpdateScreenProperties(const Eegeo::Rendering::ScreenProperties& screenProperties)
                {
                    m_camera.SetViewport(0.f, 0.f, screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight());
                }

            }
        }
    }
}