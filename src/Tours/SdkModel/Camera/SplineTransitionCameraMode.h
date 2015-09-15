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
#include "Quaternion.h"
#include "MathsHelpers.h"

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

    void GetMatrix(Eegeo::Quaternion& quaternion, Eegeo::m33& out_orientation)
    {
        float x = quaternion.x;
        float y = quaternion.y;
        float z = quaternion.z;
        float w = quaternion.w;
        out_orientation.SetRow(0, Eegeo::v3(1 - 2 * (y*y + z*z), 2 * (x*y - z*w), 2 * (x*z + y*w)));
        out_orientation.SetRow(1, Eegeo::v3(2 * (x*y + z*w), 1 - 2 * (x*x + z*z), 2 * (y*z - x*w)));
        out_orientation.SetRow(2, Eegeo::v3(2 * (x*z - y*w), 2 * (y*z + x*w), 1 - 2 * (x*x + y*y)));
        out_orientation.Transpose(out_orientation, out_orientation);
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
                class SplineTransitionCameraMode : public IToursCameraTransitionMode
                {
                public:
                    
                    SplineTransitionCameraMode(Eegeo::Geometry::CatmullRomSpline* pPositionSpline,
                                               float startFovDegrees,
                                               float endFovDegrees,
                                               Eegeo::Quaternion startOrientation,
                                               Eegeo::Quaternion endOrientation,
                                               float timeScale=0.75f)
                    : m_pPositionSpline(pPositionSpline)
                    , m_startFovDegrees(startFovDegrees)
                    , m_endFovDegrees(endFovDegrees)
                    , m_startOrientation(startOrientation)
                    , m_endOrientation(endOrientation)
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
                        Eegeo::Quaternion orientation;
                        Eegeo::m33 orientationMatrix;
                        
                        if(m_pPositionSpline == NULL ||
                           !IsValidSpineWithDifferentStartEndPoints(*m_pPositionSpline))
                        {
                            m_time = 1.f;
                            
                            
                            orientation = m_endOrientation;
                            orientation.Normalise();
                            GetMatrix(orientation, orientationMatrix);
                            SetCameraParameters(m_pPositionSpline->GetPoints().back().Position,
                                                m_pPositionSpline->GetPoints().back().Position,
                                                m_endFovDegrees,
                                                orientationMatrix);
                        }
                        else
                        {
                            m_time += (dt * m_timeScale);
                            m_time = Eegeo::Math::Clamp01(m_time);
                            
                            float t = Eegeo::Math::SmoothStep(Eegeo::Math::SmoothStep(m_time));
                            
                            Eegeo::Quaternion::Slerp(orientation, m_startOrientation, m_endOrientation, t);
                            orientation.Normalise();
                            GetMatrix(orientation, orientationMatrix);
                            
                            Eegeo::dv3 interpolatedPosition;
                            m_pPositionSpline->GetInterpolatedPositionInPlace(t, interpolatedPosition);
                            float interpolatedFov = Eegeo::Math::Lerp(m_startFovDegrees, m_endFovDegrees, t);
                            SetCameraParameters(interpolatedPosition, interpolatedPosition, interpolatedFov, orientationMatrix);
                        }
                    }
                    
                    void SetCameraParameters(const Eegeo::dv3& position,
                                             const Eegeo::dv3& target,
                                             float fov,
                                             Eegeo::m33& orientation)
                    {
                        if (Eegeo::Space::SpaceHelpers::GetAltitude(position) < 0)
                        {
                            Eegeo_TTY("ERROR, Spline takes camera under zero altitude, cancelling playback\n");
                        }
                        
                        m_cameraState.ecefPosition = position;
                        m_cameraState.ecefInterestPoint = target;
                        m_cameraState.orientationMatrix = orientation;
                        m_cameraState.fovDegrees = fov;
                    }
                    
                    bool HasEnded() const { return m_time >= 1.0f; }
                    
                    static SplineTransitionCameraMode* CreateBetweenStates(const ToursCameraState& startState, const ToursCameraState& endState);
                    
                    const ToursCameraState& GetCurrentState() const { return m_cameraState; }
                    
                private:
                    
                    ToursCameraState m_cameraState;
                    
                    Eegeo::Geometry::CatmullRomSpline* m_pPositionSpline;
                    Eegeo::Quaternion m_startOrientation;
                    Eegeo::Quaternion m_endOrientation;
                    
                    const float m_timeScale;
                    float m_time;
                    float m_startFovDegrees;
                    float m_endFovDegrees;
                    
                };
            }
        }
    }
}