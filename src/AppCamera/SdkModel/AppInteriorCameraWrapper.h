// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Camera.h"
#include "Interiors.h"
#include "IAppCamera.h"
#include "VectorMath.h"
#include <memory>

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            class AppInteriorCameraWrapper : public IAppCamera, private Eegeo::NonCopyable
            {
            public:
                
                AppInteriorCameraWrapper(const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsCameraController>& interiorCameraController);
                
                void Update(float dt);
                
                const Eegeo::Camera::CameraState GetCameraState() const;
                
                const Eegeo::Camera::RenderCamera GetRenderCamera() const;
                
                Eegeo::dv3 ComputeNonFlattenedCameraPosition() const;
                
                Eegeo::ITouchController& GetTouchController() const;
                
                Eegeo::Resources::Interiors::InteriorsCameraController& GetInteriorCameraController() const { return *m_interiorCameraController; }
                
                float GetHeadingDegrees() const;
                
            private:
                
                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsCameraController> m_interiorCameraController;
            };
        }
    }
}