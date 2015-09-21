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
                class OrbitCameraMode : public IToursCameraMode
                {
                public:
                    
                    OrbitCameraMode(const Eegeo::dv3& ecefOrigin, float radius, float orbitHeight, float angleDegrees=0.f, float rotationSpeed = 250.0f)
                    : m_ecefOrigin(ecefOrigin)
                    , m_radius(radius)
                    , m_orbitHeight(orbitHeight)
                    , m_defaultAngle(angleDegrees)
                    , m_currentAngle(angleDegrees)
                    , m_rotationSpeed(rotationSpeed)
                    {
                        Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(ecefOrigin, 0, m_tangentBasis);
                    }
                    
                    void Reset()
                    {
                        m_currentAngle = m_defaultAngle;
                    }
                    
                    void UpdateCamera(float dt,
                                      Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                      float inputScreenScale)
                    {
                        m_currentAngle += dt * 2.0f;
                        
                        float rotationDelta = touchController.GetPanPixelDelta().x * inputScreenScale * m_rotationSpeed;
                        m_currentAngle -= rotationDelta;
                        
                        m_cameraState.ecefInterestPoint = m_ecefOrigin;
                        
                        float xOffset = sinf(Eegeo::Math::Deg2Rad(m_currentAngle)) * m_radius;
                        float zOffset = -cosf(Eegeo::Math::Deg2Rad(m_currentAngle)) * m_radius;
                        m_cameraState.ecefPosition = m_ecefOrigin + Eegeo::dv3::FromSingle(
                             (m_tangentBasis.GetRight() * xOffset) +
                             (m_tangentBasis.GetForward() * zOffset) +
                             (m_tangentBasis.GetUp() * m_orbitHeight));
                        
                        Eegeo::v3 forward = (m_cameraState.ecefInterestPoint - m_cameraState.ecefPosition).Norm().ToSingle();
                        Eegeo::v3 up = m_cameraState.ecefPosition.Norm().ToSingle();
                        Eegeo::v3 right = Eegeo::v3::Cross(up, forward).Norm();
                        up = Eegeo::v3::Cross(forward, right).Norm();
                        
                        m_cameraState.orientationMatrix.SetFromBasis(right, up, forward);
                        m_cameraState.fovDegrees = 40.0f;
                    }
                    
                    const ToursCameraState& GetCurrentState() const { return m_cameraState; }
                    
                private:
                    
                    ToursCameraState m_cameraState;
                    
                    Eegeo::Space::EcefTangentBasis m_tangentBasis;
                    
                    Eegeo::dv3 m_ecefOrigin;
                    float m_radius;
                    float m_orbitHeight;
                    float m_defaultAngle;
                    float m_currentAngle;
                    float m_rotationSpeed;
                };
            }
        }
    }
}