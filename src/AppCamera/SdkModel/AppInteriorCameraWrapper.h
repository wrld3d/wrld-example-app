// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Camera.h"
#include "Interiors.h"
#include "IAppCamera.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            class AppInteriorCameraWrapper : public IAppCamera
            {
            public:
                
                AppInteriorCameraWrapper(Eegeo::Resources::Interiors::InteriorsGpsCameraController& interiorGpsCameraController,
                                         Eegeo::Resources::Interiors::InteriorsCameraController& interiorCameraController);
                
                void Update(float dt);
                
                const Eegeo::Camera::CameraState GetCameraState() const;
                
                const Eegeo::Camera::RenderCamera GetRenderCamera() const;
                
                Eegeo::dv3 ComputeNonFlattenedCameraPosition() const;
                
                Eegeo::ITouchController& GetTouchController() const;
                
                Eegeo::Resources::Interiors::InteriorsGpsCameraController& GetInteriorGpsCameraController() const { return m_interiorGpsCameraController; }
                
                Eegeo::Resources::Interiors::InteriorsCameraController& GetInteriorCameraController() const { return m_interiorCameraController; }
                
                float GetHeadingDegrees() const;
                
            private:
                
                Eegeo::Resources::Interiors::InteriorsGpsCameraController& m_interiorGpsCameraController;
                Eegeo::Resources::Interiors::InteriorsCameraController& m_interiorCameraController;
            };
        }
    }
}