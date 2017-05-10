// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IAppCameraController.h"
#include "IAppCamera.h"
#include "Camera.h"
#include <map>
#include "GlobeCameraController.h"
#include "VectorMathDecl.h"
#include "ITouchController.h"

namespace ExampleApp
{
    namespace AppCamera
    {
        namespace SdkModel
        {
            class AppCameraController : public IAppCameraController
            {
            private:
                
                std::map<int, IAppCamera*> m_cameras;
                
                Eegeo::Camera::RenderCamera m_renderCamera;
                
                int m_currentCameraIndex;
                int m_previousCameraIndex;
                bool m_isTransitionInFlight;
                float m_transitionTimer;
                float m_transitionDuration;
                double m_jumpThresholdDistanceBetweenCameras;
                
                Eegeo::dv3 m_currentPosition;
                Eegeo::m33 m_currentOrientation;
                Eegeo::dv3 m_currentInterestPoint;
                
                Eegeo::dv3 m_currentNonFlattenedCameraPosition;
                
                Eegeo::Helpers::CallbackCollection0 m_transitionInFlightChangedCallbacks;

                float m_transitionTimeMultiplier;
                
                void UpdateTransitionBetween(IAppCamera& previousCamera, IAppCamera& nextCamera, float dt);
                const bool ShouldSkipTransition(IAppCamera& previousCamera, IAppCamera& nextCamera);
                
            public:
                
                AppCameraController();
                ~AppCameraController();
                
                int CreateCameraHandleFromController(IAppCamera& cameraController);
                
                void RemoveCameraHandle(int cameraHandle);
                
                void TransitionToCameraWithHandle(int cameraHandle);
                void TransitionToCameraWithHandle(int cameraHandle, const double jumpThresholdDistanceBetweenCameras, const float transitionDuration);
                void SetTransitionTimeMultiplier(float newMultiplier);
                
                const bool IsTransitionInFlight() const;
                
                const Eegeo::Camera::CameraState GetCameraState();
                
                const Eegeo::Camera::RenderCamera& GetRenderCamera();
                
                Eegeo::dv3 GetNonFlattenedCameraPosition() const;
                
                Eegeo::ITouchController& GetTouchController();
                
                float GetHeadingDegrees() const;
                
                void Update(float dt);
                
                void InsertTransitioInFlightChangedCallback(Eegeo::Helpers::ICallback0& callback);
                void RemoveTransitioInFlightChangedCallback(Eegeo::Helpers::ICallback0& callback);
            };
        }
    }
}
