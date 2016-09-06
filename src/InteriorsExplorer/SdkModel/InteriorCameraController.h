// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "IInteriorCameraController.h"
#include "VectorMathDecl.h"
#include "Types.h"
#include "GlobeCamera.h"
#include "InteriorsCameraController.h"
#include <memory>

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorCameraController : public IInteriorCameraController, private Eegeo::NonCopyable
            {
            public:
                InteriorCameraController(const std::shared_ptr<Eegeo::Camera::GlobeCamera::GlobeCameraTouchController>& touchController,
                                         const std::shared_ptr<Eegeo::Camera::GlobeCamera::GlobeCameraController>& globeCameraController,
                                         const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsCameraController>& interiorsCameraController);
                
                void SetInterestLocation(const Eegeo::dv3& interestPointEcef);
                const Eegeo::dv3& GetInterestLocation() const;
                
                void SetDistanceToInterest(float distanceMeters);
                const float GetDistanceToInterest() const;
                
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsCameraController>& GetSdkController() const
                {
                    return m_interiorsCameraController;
                }

                const std::shared_ptr<Eegeo::Camera::GlobeCamera::GlobeCameraTouchController>& GetTouchController() const
                {
                    return m_touchCameraController;
                }
                
            private:
                const std::shared_ptr<Eegeo::Camera::GlobeCamera::GlobeCameraTouchController> m_touchCameraController;
                const std::shared_ptr<Eegeo::Camera::GlobeCamera::GlobeCameraController> m_globeCameraController;
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsCameraController> m_interiorsCameraController;
            };
        }
    }
}