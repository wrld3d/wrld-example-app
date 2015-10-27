// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InterestPointTransitionCameraMode.h"

#include "MathsHelpers.h"
#include "Quaternion.h"
#include "SpaceHelpers.h"
#include "Types.h"


namespace
{    
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
                InterestPointTransitionCameraMode* InterestPointTransitionCameraMode::CreateBetweenStates(const ToursCameraState& startState, const ToursCameraState& endState)
                {
                    const Eegeo::dv3& startInterestPoint = startState.ecefInterestPoint;
                    const Eegeo::dv3& endInterestPoint = endState.ecefInterestPoint;
                    double startDistanceToInterest = (startInterestPoint - startState.ecefPosition).Length();
                    double endDistanceToInterest = (endInterestPoint - endState.ecefPosition).Length();
                    
                    Eegeo::Quaternion startOrientation = Eegeo::Quaternion::ExtractQuaternion(startState.orientationMatrix);
                    Eegeo::Quaternion endOrientation = Eegeo::Quaternion::ExtractQuaternion(endState.orientationMatrix);
                    
                    startOrientation.Normalise();
                    endOrientation.Normalise();

                    return Eegeo_NEW(InterestPointTransitionCameraMode)(startInterestPoint, endInterestPoint, startDistanceToInterest, endDistanceToInterest, startState.fovDegrees, endState.fovDegrees, startOrientation, endOrientation);
                }
                
                InterestPointTransitionCameraMode::InterestPointTransitionCameraMode(
                                                  const Eegeo::dv3& startInterestPoint,
                                                  const Eegeo::dv3& endInterestPoint,
                                                  double startDistanceToInterest,
                                                  double endDistanceToInterest,
                                                  float startFovDegrees,
                                                  float endFovDegrees,
                                                  Eegeo::Quaternion startOrientation,
                                                  Eegeo::Quaternion endOrientation,
                                                  float timeScale)
                : m_startInterestPoint(startInterestPoint)
                , m_endInterestPoint(endInterestPoint)
                , m_startDistanceToInterest(startDistanceToInterest)
                , m_endDistanceToInterest(endDistanceToInterest)
                , m_startFovDegrees(startFovDegrees)
                , m_endFovDegrees(endFovDegrees)
                , m_startOrientation(startOrientation)
                , m_endOrientation(endOrientation)
                , m_time(0.0f)
                , m_timeScale(timeScale)
                {
                }
                
                void InterestPointTransitionCameraMode::UpdateCamera(
                                  float dt,
                                  Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& touchController,
                                  float inputScreenScale)
                {
                    Eegeo::Quaternion orientation;
                    Eegeo::m33 orientationMatrix;
                    
                    m_time += (dt * m_timeScale);
                    m_time = Eegeo::Math::Clamp01(m_time);
                    
                    float t = Eegeo::Helpers::MathsHelpers::PennerQuadraticEaseInOut(m_time, 0.0f, 1.0f, 1.0f);
                    
                    Eegeo::Quaternion::Slerp(orientation, m_startOrientation, m_endOrientation, t);
                    orientation.Normalise();
                    GetMatrix(orientation, orientationMatrix);
                    
                    double interpolatedDistanceToInterest = Eegeo::Math::Lerp(m_startDistanceToInterest, m_endDistanceToInterest, (double)t);
                    
                    Eegeo::dv3 interpolatedInterestPoint = Eegeo::dv3::Lerp(m_startInterestPoint, m_endInterestPoint, t);
                    
                    Eegeo::dv3 distanceVector = -orientationMatrix.GetRow(2).Norm()*interpolatedDistanceToInterest;
                    Eegeo::dv3 interpolatedPosition = distanceVector + interpolatedInterestPoint;
                    
                    float interpolatedFov = Eegeo::Math::Lerp(m_startFovDegrees, m_endFovDegrees, t);
                    SetCameraParameters(interpolatedPosition, interpolatedInterestPoint, interpolatedFov, orientationMatrix);
                }
                
                void InterestPointTransitionCameraMode::SetCameraParameters(const Eegeo::dv3& position,
                                         const Eegeo::dv3& target,
                                         float fov,
                                         Eegeo::m33& orientation)
                {
                    if (Eegeo::Space::SpaceHelpers::GetAltitude(position) < 0)
                    {
                        Eegeo_TTY("ERROR, Interest transition takes camera under zero altitude, cancelling playback\n");
                    }
                    
                    m_cameraState.ecefPosition = position;
                    m_cameraState.ecefInterestPoint = target;
                    m_cameraState.orientationMatrix = orientation;
                    m_cameraState.fovDegrees = fov;
                }
            }
        }
    }
}