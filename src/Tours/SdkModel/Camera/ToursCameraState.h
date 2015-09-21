// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "VectorMath.h"
#include "CameraState.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                struct ToursCameraState
                {
                public:
                    
                    ToursCameraState()
                    : ecefPosition(Eegeo::dv3::Zero())
                    , ecefInterestPoint(Eegeo::dv3::Zero())
                    , fovDegrees(40)
                    {
                        orientationMatrix.Identity();
                    }
                    
                    Eegeo::m33 orientationMatrix;
                    Eegeo::dv3 ecefPosition;
                    Eegeo::dv3 ecefInterestPoint;
                    float fovDegrees;
                    
                    static ToursCameraState CreateFromCameraState(const Eegeo::Camera::CameraState& appCameraState, float fov)
                    {
                        ToursCameraState toursCameraState;
                        toursCameraState.ecefPosition = appCameraState.LocationEcef();
                        toursCameraState.ecefInterestPoint = appCameraState.InterestPointEcef();
                        Eegeo::m33::Transpose(toursCameraState.orientationMatrix, appCameraState.ViewMatrix());
                        toursCameraState.fovDegrees = fov;
                        return toursCameraState;
                    }
                };
            }
        }
    }
}