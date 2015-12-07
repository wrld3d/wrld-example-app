// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IToursCameraTransitionMode.h"

#include "Quaternion.h"
#include "VectorMath.h"
#include "ToursCameraState.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                class InterestPointTransitionCameraMode : public IToursCameraTransitionMode
                {
                public:
                    
                    InterestPointTransitionCameraMode(const Eegeo::dv3& startInterestPoint,
                                                      const Eegeo::dv3& endInterestPoint,
                                                      double startDistanceToInterest,
                                                      double endDistanceToInterest,
                                                      float startFovDegrees,
                                                      float endFovDegrees,
                                                      Eegeo::Quaternion startOrientation,
                                                      Eegeo::Quaternion endOrientation,
                                                      bool jumpIfFar);
                    void Reset()
                    {
                        m_time = 0.0f;
                    }
                    
                    void UpdateCamera(float dt,
                                      Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                      float inputScreenScale);
                    
                    void SetCameraParameters(const Eegeo::dv3& position,
                                             const Eegeo::dv3& target,
                                             float fov,
                                             Eegeo::m33& orientation);
                    
                    bool HasEnded() const { return m_time >= 1.0f; }
                    
                    static InterestPointTransitionCameraMode* CreateBetweenStates(const ToursCameraState& startState, const ToursCameraState& endState, bool jumpIfFar);
                    
                    const ToursCameraState& GetCurrentState() const { return m_cameraState; }
                    
                private:
                    
                    ToursCameraState m_cameraState;
                    
                    Eegeo::dv3 m_startInterestPoint;
                    Eegeo::dv3 m_endInterestPoint;
                    
                    double m_startDistanceToInterest;
                    double m_endDistanceToInterest;
                    
                    Eegeo::Quaternion m_startOrientation;
                    Eegeo::Quaternion m_endOrientation;
                    
                    float m_timeScale;
                    float m_time;
                    float m_startFovDegrees;
                    float m_endFovDegrees;
                    
                };
            }
        }
    }
}