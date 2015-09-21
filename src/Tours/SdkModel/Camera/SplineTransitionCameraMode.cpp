// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "Types.h"
#include "SplineTransitionCameraMode.h"
#include "Quaternion.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                SplineTransitionCameraMode* SplineTransitionCameraMode::CreateBetweenStates(const ToursCameraState& startState, const ToursCameraState& endState)
                {
                    Eegeo::Geometry::CatmullRomSpline* positionSpline = new Eegeo::Geometry::CatmullRomSpline();
                    positionSpline->AddPoint(startState.ecefPosition);
                    positionSpline->AddPoint(endState.ecefPosition);
                    positionSpline->SetTimeParameterizationMethod(Eegeo::Geometry::TimeParameterizationMethod::Uniform);
                    
                    Eegeo::Quaternion startOrientation = Eegeo::Quaternion::ExtractQuaternion(startState.orientationMatrix);
                    Eegeo::Quaternion endOrientation = Eegeo::Quaternion::ExtractQuaternion(endState.orientationMatrix);

                    return Eegeo_NEW(SplineTransitionCameraMode)(positionSpline, startState.fovDegrees, endState.fovDegrees, startOrientation, endOrientation);
                }
            }
        }
    }
}