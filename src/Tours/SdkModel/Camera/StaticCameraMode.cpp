// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "StaticCameraMode.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                // Look at a location but wobble slightly so it's not completely static.
                StaticCameraMode::StaticCameraMode(const Eegeo::dv3& ecefInterestPoint,
                                                   float pitchDegrees,
                                                   float distanceCameraToInterest,
                                                   float originRotation)
                {
                    const float pitchRadians = Eegeo::Math::Deg2Rad(pitchDegrees);
                    Eegeo::Space::EcefTangentBasis tangentBasis;
                    Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(ecefInterestPoint, originRotation, tangentBasis);
                    
                    Eegeo::dv3 cameraPosition;
                    Eegeo::v3 cameraDirection;
                    Eegeo::v3 cameraUp;
                    
                    Eegeo::Camera::CameraHelpers::CalculateLookAt(ecefInterestPoint,
                                                                  tangentBasis.GetForward(),
                                                                  pitchRadians,
                                                                  distanceCameraToInterest,
                                                                  cameraPosition,
                                                                  cameraDirection,
                                                                  cameraUp);
                    
                    const Eegeo::v3 right = Eegeo::v3::Cross(cameraUp, cameraDirection).Norm();
                    
                    m_cameraState.ecefPosition = cameraPosition;
                    m_cameraState.ecefInterestPoint = ecefInterestPoint;
                    m_cameraState.orientationMatrix.SetFromBasis(right, cameraUp, cameraDirection);
                    
                }
            }
        }
    }
}
