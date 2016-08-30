// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppInteriorCameraWrapper.h"
#include "InteriorsCameraController.h"
#include "CameraHelpers.h"
#include "CameraState.h"
#include "RenderCamera.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            AppInteriorCameraWrapper::AppInteriorCameraWrapper(const std::shared_ptr<Eegeo::Resources::Interiors::InteriorsCameraController>& interiorCameraController)
            : m_interiorCameraController(interiorCameraController)
            {
            }
            
            void AppInteriorCameraWrapper::Update(float dt)
            {
                m_interiorCameraController->Update(dt);
            }
            
            const Eegeo::Camera::CameraState AppInteriorCameraWrapper::GetCameraState() const
            {
                return m_interiorCameraController->GetCameraState();
            }
            
            const Eegeo::Camera::RenderCamera AppInteriorCameraWrapper::GetRenderCamera() const
            {
                return m_interiorCameraController->GetRenderCamera();
            }
            
            Eegeo::dv3 AppInteriorCameraWrapper::ComputeNonFlattenedCameraPosition() const
            {
                return m_interiorCameraController->ComputeNonFlattenedCameraPosition();
            }
            
            Eegeo::ITouchController& AppInteriorCameraWrapper::GetTouchController() const
            {
                return m_interiorCameraController->GetTouchController();
            }
            
            float AppInteriorCameraWrapper::GetHeadingDegrees() const
            {
                return m_interiorCameraController->GetHeadingDegrees();
            }
        }
    }
}