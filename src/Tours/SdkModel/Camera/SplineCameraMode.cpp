// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "Types.h"
#include "SplineCameraMode.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                SplineCameraMode* SplineCameraMode::CreateBetweenStates(const ToursCameraState& startState, const ToursCameraState& endState)
                {
                    Eegeo::Geometry::CatmullRomSpline* positionSpline = new Eegeo::Geometry::CatmullRomSpline();
                    positionSpline->AddPoint(startState.ecefPosition);
                    positionSpline->AddPoint(endState.ecefPosition);
                    positionSpline->SetTimeParameterizationMethod(Eegeo::Geometry::TimeParameterizationMethod::Chordal);
                    
                    Eegeo::Geometry::CatmullRomSpline* targetSpline = new Eegeo::Geometry::CatmullRomSpline();
                    targetSpline->AddPoint(startState.ecefInterestPoint);
                    targetSpline->AddPoint(endState.ecefInterestPoint);
                    targetSpline->SetTimeParameterizationMethod(Eegeo::Geometry::TimeParameterizationMethod::Uniform);
                    
                    return Eegeo_NEW(SplineCameraMode)(positionSpline, targetSpline, startState.fovDegrees, endState.fovDegrees);
                }
            }
        }
    }
}