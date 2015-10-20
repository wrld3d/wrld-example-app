// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppCameraController.h"
#include "VectorMath.h"
#include "MathFunc.h"
#include "RenderCamera.h"
#include "CameraState.h"
#include "Quaternion.h"
#include "AppCameraHelpers.h"
#include "CameraHelpers.h"
#include "EcefTangentBasis.h"
#include "MathsHelpers.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            namespace
            {
                static int nextHandleId = -1;
            }
            
            AppCameraController::AppCameraController()
            : m_currentCameraIndex(0)
            , m_previousCameraIndex(0)
            , m_transitionDuration(0.75f)
            , m_transitionTimer(0.0f)
            {
                nextHandleId = -1;
            }
            
            AppCameraController::~AppCameraController()
            {
                
            }
            
            int AppCameraController::CreateCameraHandleFromController(IAppCamera& cameraController)
            {
                m_cameras.insert(std::make_pair(++nextHandleId, &cameraController));
                
                return nextHandleId;
            }
            
            void AppCameraController::RemoveCameraHandle(int cameraHandle)
            {
                m_cameras.erase(cameraHandle);
            }
            
            void AppCameraController::TransitionToCameraWithHandle(int cameraHandle)
            {
                Eegeo_ASSERT(cameraHandle < static_cast<int>(m_cameras.size()), "Invalid camera Id");
                
                m_transitionTimer = 0.0f;
                m_isTransitionInFlight = true;
                
                m_previousCameraIndex = m_currentCameraIndex;
                m_currentCameraIndex = cameraHandle;
            }

            const bool AppCameraController::IsTransitionInFlight() const
            {
                return m_isTransitionInFlight;
            }
            
            const Eegeo::Camera::CameraState AppCameraController::GetCameraState()
            {
                return m_isTransitionInFlight ? Eegeo::Camera::CameraState(m_renderCamera.GetEcefLocation(),
                                                                           m_renderCamera.GetEcefLocation(),
                                                                           m_renderCamera.GetViewMatrix(),
                                                                           m_renderCamera.GetProjectionMatrix())
                                              : m_cameras[m_currentCameraIndex]->GetCameraState();
            }
            
            const Eegeo::Camera::RenderCamera& AppCameraController::GetRenderCamera()
            {
                return m_renderCamera;
            }
            
            Eegeo::ITouchController& AppCameraController::GetTouchController()
            {
                return m_cameras[m_currentCameraIndex]->GetTouchController();
            }
            
            void AppCameraController::Update(float dt)
            {
                if(m_isTransitionInFlight)
                {
                    m_transitionTimer = Eegeo::Math::Clamp(m_transitionTimer + dt, 0.0f, m_transitionDuration);
                    
                    if(m_transitionTimer >= m_transitionDuration)
                    {
                        m_isTransitionInFlight = false;
                    }
                    
                    UpdateTransitionBetween(*m_cameras[m_previousCameraIndex], *m_cameras[m_currentCameraIndex], dt);
                }
                else
                {
                    m_cameras[m_currentCameraIndex]->Update(dt);
                    m_renderCamera = m_cameras[m_currentCameraIndex]->GetRenderCamera();
                }
            }
            
            void AppCameraController::UpdateTransitionBetween(IAppCamera &previousCamera, IAppCamera &nextCamera, float dt)
            {
                previousCamera.Update(dt);
                nextCamera.Update(dt);
                
                const Eegeo::Camera::RenderCamera startCamera = previousCamera.GetRenderCamera();
                const Eegeo::Camera::RenderCamera endCamera = nextCamera.GetRenderCamera();
                
                float t = Eegeo::Math::Clamp01(m_transitionTimer/m_transitionDuration);
                float easedT = Eegeo::Helpers::MathsHelpers::PennerQuadraticEaseInOut(t, 0.0f, 1.0f, 1.0f);
                
                const Eegeo::dv3 startPos = startCamera.GetEcefLocation();
                const Eegeo::dv3 endPos = endCamera.GetEcefLocation();
                m_currentPosition = Eegeo::dv3::Lerp(startPos, endPos, easedT);
                
                const Eegeo::m33 startOrientation = startCamera.GetModelMatrix();
                const Eegeo::m33 endOrientation = endCamera.GetModelMatrix();
                
                const Eegeo::Quaternion startRotation = Eegeo::Quaternion::ExtractQuaternion(startOrientation);
                const Eegeo::Quaternion endRotation = Eegeo::Quaternion::ExtractQuaternion(endOrientation);
                
                Eegeo::Quaternion currentRotation;
                Eegeo::Quaternion::Slerp(currentRotation, startRotation, endRotation, easedT);
                Helpers::GetMatrixFromQuaternion(currentRotation, m_currentOrientation);
                
                const float fov = Eegeo::Math::Lerp(startCamera.GetFOV(), endCamera.GetFOV(), easedT);
                const float near = Eegeo::Math::Lerp(startCamera.GetNearClip(), endCamera.GetNearClip(), easedT);
                const float far = Eegeo::Math::Lerp(startCamera.GetFarClip(), endCamera.GetFarClip(), easedT);
                
                m_renderCamera.SetProjection(fov, near, far);
                m_renderCamera.SetEcefLocation(m_currentPosition);
                m_renderCamera.SetOrientationMatrix(m_currentOrientation);
            }
        }
    }
}