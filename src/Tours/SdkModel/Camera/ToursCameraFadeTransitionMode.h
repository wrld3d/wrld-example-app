// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IToursCameraTransitionMode.h"
#include "ToursCameraState.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                class ToursCameraFadeTransitionMode : public IToursCameraTransitionMode
                {
                    ToursCameraState m_cameraDestinationState;
                    float m_transitionLengthTime;
                    float m_time;
                    
                public:
                    ToursCameraFadeTransitionMode(const ToursCameraState& cameraDestinationState,
                                                  float transitionLengthTime);
                    
                    ~ToursCameraFadeTransitionMode();
                    
                    bool HasEnded() const;
                    
                    void UpdateCamera(float dt,
                                      Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                      float inputScreenScale);
                    
                    const ToursCameraState& GetCurrentState() const;
                    
                    void Reset();
                };
            }
        }
    }
}