// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "InteriorCameraController.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorCameraController::InteriorCameraController(const std::shared_ptr<Eegeo::Camera::GlobeCamera::GlobeCameraTouchController>& touchController,
                                     const std::shared_ptr<Eegeo::Camera::GlobeCamera::GlobeCameraController>& globeCameraController,
                                     const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsCameraController>& interiorsCameraController)
            : m_touchCameraController(touchController)
            , m_globeCameraController(globeCameraController)
            , m_interiorsCameraController(interiorsCameraController)
            {
            }
            
            void InteriorCameraController::SetInterestLocation(const Eegeo::dv3& interestPointEcef)
            {
                m_interiorsCameraController->SetInterestLocation(interestPointEcef);
            }
            
            const Eegeo::dv3& InteriorCameraController::GetInterestLocation() const
            {
                return m_interiorsCameraController->GetInterestLocation();
            }
            
            void InteriorCameraController::SetDistanceToInterest(float distanceMeters)
            {
                m_interiorsCameraController->SetDistanceToInterest(distanceMeters);
            }
            
            const float InteriorCameraController::GetDistanceToInterest() const
            {
                return m_interiorsCameraController->GetDistanceToInterest();
            }
        }
    }
}