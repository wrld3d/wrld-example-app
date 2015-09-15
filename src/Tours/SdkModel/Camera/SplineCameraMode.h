// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IToursCameraTransitionMode.h"
#include "VectorMath.h"
#include "EcefTangentBasis.h"
#include "CameraHelpers.h"
#include "MathFunc.h"
#include "GlobeCameraTouchController.h"
#include "EarthConstants.h"
#include "ToursCameraState.h"
#include "ISpline.h"
#include "CatmullRomSpline.h"
#include "SpaceHelpers.h"

namespace
{
    bool IsValidSpineWithDifferentStartEndPoints(const Eegeo::Geometry::CatmullRomSpline& spline)
    {
        if(!spline.IsValid())
        {
            return false;
        }
        
        if(spline.GetNumberOfPoints() < 2)
        {
            return false;
        }
        
        const Eegeo::Geometry::CatmullRomSplinePoint& start(spline.GetPoints().front());
        const Eegeo::Geometry::CatmullRomSplinePoint& end(spline.GetPoints().back());
        
        if((start.Position - end.Position).LengthSq() < 0.01)
        {
            return false;
        }
        
        if(std::isnan(start.T) || std::isnan(end.T))
        {
            return false;
        }
        
        return true;
    }
}

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                class SplineCameraMode : public IToursCameraTransitionMode
                {
                public:
                    
                    SplineCameraMode(Eegeo::Geometry::CatmullRomSpline* pPositionSpline,
                                     Eegeo::Geometry::CatmullRomSpline* pTargetSpline,
                                     float startFovDegrees,
                                     float endFovDegrees,
                                     float timeScale=1.f)
                    : m_pPositionSpline(pPositionSpline)
                    , m_pTargetSpline(pTargetSpline)
                    , m_startFovDegrees(startFovDegrees)
                    , m_endFovDegrees(endFovDegrees)
                    , m_time(0.0f)
                    , m_timeScale(timeScale)
                    {
                    }
                    
                    void Reset()
                    {
                        m_time = 0.0f;
                    }
                    
                    void UpdateCamera(float dt,
                                      Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                      float inputScreenScale)
                    {
                        if(m_pPositionSpline == NULL || m_pTargetSpline == NULL ||
                           !IsValidSpineWithDifferentStartEndPoints(*m_pPositionSpline) || !m_pTargetSpline->IsValid())
                        {
                            m_time = 1.f;
                            
                            SetCameraParameters(m_pPositionSpline->GetPoints().back().Position,
                                                m_pTargetSpline->GetPoints().back().Position,
                                                m_endFovDegrees);
                        }
                        else
                        {
                            m_time += (dt * m_timeScale);
                            m_time = Eegeo::Math::Clamp01(m_time);
                            float smoothT = Eegeo::Math::SmoothStep(m_time);
                            
                            Eegeo::dv3 interpolatedPosition, interpolatedTarget;
                            m_pPositionSpline->GetInterpolatedPositionInPlace(smoothT, interpolatedPosition);
                            m_pTargetSpline->GetInterpolatedPositionInPlace(smoothT, interpolatedTarget);
                            float interpolatedFov = Eegeo::Math::Lerp(m_startFovDegrees, m_endFovDegrees, smoothT);
                            SetCameraParameters(interpolatedPosition, interpolatedTarget, interpolatedFov);
                        }
                    }
                    
                    void SetCameraParameters(const Eegeo::dv3& position,
                                             const Eegeo::dv3& target,
                                             float fov)
                    {
                        if (Eegeo::Space::SpaceHelpers::GetAltitude(position) < 0)
                        {
                            Eegeo_TTY("ERROR, Spline takes camera under zero altitude, cancelling playback\n");
                        }
                        
                        m_cameraState.ecefPosition = position;
                        
                        m_cameraState.ecefInterestPoint = target;
                        Eegeo::v3 direction = (target - m_cameraState.ecefPosition).Norm().ToSingle();
                        Eegeo::v3 up = m_cameraState.ecefPosition.Norm().ToSingle();
                        Eegeo::v3 right = Eegeo::v3::Cross(up, direction).Norm();
                        if(!Eegeo::v3::IsFinite(right))
                        {
                            Eegeo::Space::EcefTangentBasis tangentBasis;
                            Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(target, 0, tangentBasis);
                            right = tangentBasis.GetRight().Norm();
                        }
                        up = Eegeo::v3::Cross(direction, right).Norm();
                        
                        m_cameraState.orientationMatrix.SetFromBasis(right, up, direction);
                        m_cameraState.fovDegrees = fov;
                    }
                    
                    bool HasEnded() const { return m_time >= 1.0f; }
                    
                    float InterpolationState() const { return m_time; }
                    
                    static SplineCameraMode* CreateBetweenStates(const ToursCameraState& startState, const ToursCameraState& endState);
                    
                    const ToursCameraState& GetCurrentState() const { return m_cameraState; }
                    
                private:
                    
                    ToursCameraState m_cameraState;
                    
                    Eegeo::Geometry::CatmullRomSpline* m_pPositionSpline;
                    Eegeo::Geometry::CatmullRomSpline* m_pTargetSpline;
                    
                    const float m_timeScale;
                    float m_time;
                    float m_startFovDegrees;
                    float m_endFovDegrees;
                    
                };
            }
        }
    }
}