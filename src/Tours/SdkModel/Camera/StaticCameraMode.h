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
                class StaticCameraMode : public IToursCameraMode
                {
                public:
                    StaticCameraMode(const Eegeo::dv3& ecefInterestPoint,
                                     float pitchDegrees,
                                     float distanceCameraToInterest,
                                     float originRotationDegrees = 0.0f);
                    
                    void Reset() {}
                    
                    void UpdateCamera(float dt,
                                      Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                      float inputScreenScale) {}
                    
                    const ToursCameraState& GetCurrentState() const { return m_cameraState; }
                    
                private:
                    
                    ToursCameraState m_cameraState;
                };
            }
        }
    }
}