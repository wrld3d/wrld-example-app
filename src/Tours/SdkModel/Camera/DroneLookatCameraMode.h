// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IToursCameraMode.h"
#include "VectorMath.h"
#include "EcefTangentBasis.h"
#include "CameraHelpers.h"
#include "MathFunc.h"
#include "GlobeCameraTouchController.h"
#include "EarthConstants.h"
#include "ToursCameraState.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                // Look at a location but wobble slightly so it's not completely static.
                class DroneLookatCameraMode : public IToursCameraMode
                {
                public:
                    DroneLookatCameraMode(const Eegeo::dv3& ecefOrigin, const Eegeo::dv3& ecefTarget, float noiseRadius, float originRotation = 0.0f)
                    : m_ecefOrigin(ecefOrigin)
                    , m_ecefTarget(ecefTarget)
                    , m_noiseRadius(noiseRadius)
                    , m_noiseTimer(0.0f)
                    {
                        if(originRotation > 0.0001f)
                        {
                            Eegeo::dv3 targetAxis = m_ecefTarget.Norm();
                            Eegeo::dv3 originOffset = m_ecefOrigin - m_ecefTarget;
                            
                            Eegeo::dm44 axisRotation;
                            axisRotation.Identity();
                            axisRotation.Rotate(targetAxis, originRotation);
                            
                            originOffset = Eegeo::dv3::Mul(originOffset, axisRotation);
                            
                            m_ecefOrigin = ecefTarget + originOffset;
                        }
                    }
                    
                    void Reset()
                    {
                        m_noiseTimer = 0.0f;
                    }
                    
                    void UpdateCamera(float dt,
                                      Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                      float inputScreenScale)
                    {
                        m_noiseTimer += dt;
                        
                        Eegeo::v3 at = (m_ecefTarget - m_ecefOrigin).Norm().ToSingle();
                        Eegeo::v3 up = m_ecefOrigin.Norm().ToSingle();
                        Eegeo::v3 right = Eegeo::v3::Cross(up, at).Norm();
                        up = Eegeo::v3::Cross(at, right).Norm();
                        
                        float noiseX = sinf(m_noiseTimer * 0.4f) * m_noiseRadius;
                        float noiseY = -cosf(m_noiseTimer * 0.572f) * m_noiseRadius;
                        
                        Eegeo::v3 noise = (right * noiseX) + (up * noiseY);
                        Eegeo::dv3 finalPosition = m_ecefOrigin + Eegeo::dv3::FromSingle(noise);
                        Eegeo::dv3 finalTarget = m_ecefTarget + Eegeo::dv3::FromSingle(noise * 0.25f);
                        
                        m_cameraState.ecefPosition = finalPosition;
                        m_cameraState.ecefInterestPoint = finalTarget;
                        
                        at = (finalTarget - finalPosition).Norm().ToSingle();
                        up = Eegeo::v3::Cross(at, right).Norm();
                        right = Eegeo::v3::Cross(up, at).Norm();
                        m_cameraState.orientationMatrix.SetFromBasis(right, up, at);
                        
                        m_cameraState.fovDegrees = 40.0f;
                    }
                    
                    const ToursCameraState& GetCurrentState() const { return m_cameraState; }
                    
                private:
                    
                    ToursCameraState m_cameraState;
                    
                    Eegeo::dv3 m_ecefOrigin;
                    Eegeo::dv3 m_ecefTarget;
                    float m_noiseRadius;
                    float m_noiseTimer;
                };
            }
        }
    }
}