// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ToursCameraFadeTransitionMode.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                ToursCameraFadeTransitionMode::ToursCameraFadeTransitionMode(const ToursCameraState& cameraDestinationState,
                                                                             float transitionLengthTime)
                : m_cameraDestinationState(cameraDestinationState)
                , m_transitionLengthTime(transitionLengthTime)
                , m_time(0.f)
                {
                    
                }
                
                ToursCameraFadeTransitionMode::~ToursCameraFadeTransitionMode()
                {
                    
                }
                
                bool ToursCameraFadeTransitionMode::HasEnded() const
                {
                    return m_time >= m_transitionLengthTime;
                }
                
                void ToursCameraFadeTransitionMode::UpdateCamera(float dt,
                                                                 Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                                                 float inputScreenScale)
                {
                    m_time += dt;
                }
                
                const ToursCameraState& ToursCameraFadeTransitionMode::GetCurrentState() const
                {
                    return m_cameraDestinationState;
                }
                
                void ToursCameraFadeTransitionMode::Reset()
                {
                    m_time = 0.f;
                }
            }
        }
    }
}