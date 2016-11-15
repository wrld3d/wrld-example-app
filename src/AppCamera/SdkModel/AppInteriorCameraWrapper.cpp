// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "AppInteriorCameraWrapper.h"
#include "InteriorsCameraController.h"
#include "InteriorsGpsCameraController.h"
#include "CameraHelpers.h"
#include "CameraState.h"
#include "RenderCamera.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            AppInteriorCameraWrapper::AppInteriorCameraWrapper(Eegeo::Resources::Interiors::InteriorsGpsCameraController& interiorGpsCameraController,
                                                               Eegeo::Resources::Interiors::InteriorsCameraController& interiorCameraController)
            : m_interiorGpsCameraController(interiorGpsCameraController)
            , m_interiorCameraController(interiorCameraController)
            {
            }
            
            void AppInteriorCameraWrapper::Update(float dt)
            {
                m_interiorGpsCameraController.Update(dt);
            }
            
            const Eegeo::Camera::CameraState AppInteriorCameraWrapper::GetCameraState() const
            {
                return m_interiorGpsCameraController.GetCameraState();
            }
            
            const Eegeo::Camera::RenderCamera AppInteriorCameraWrapper::GetRenderCamera() const
            {
                return m_interiorGpsCameraController.GetRenderCamera();
            }
            
            Eegeo::dv3 AppInteriorCameraWrapper::ComputeNonFlattenedCameraPosition() const
            {
                return m_interiorGpsCameraController.ComputeNonFlattenedCameraPosition();
            }
            
            Eegeo::ITouchController& AppInteriorCameraWrapper::GetTouchController() const
            {
                return m_interiorGpsCameraController.GetTouchController();
            }
            
            float AppInteriorCameraWrapper::GetHeadingDegrees() const
            {
                return m_interiorGpsCameraController.GetHeadingDegrees();
            }
        }
    }
}