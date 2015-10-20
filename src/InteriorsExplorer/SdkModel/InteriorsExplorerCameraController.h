// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IAppCamera.h"
#include "GlobeCamera.h"
#include "ICallback.h"
#include "Interiors.h"
#include "ITouchController.h"
#include "VectorMath.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorsExplorerCameraController : public AppCamera::SdkModel::IAppCamera, private Eegeo::NonCopyable
            {
            private:
                bool m_cameraTouchEnabled;
                Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& m_markerRepository;
                Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController;
                Eegeo::Camera::GlobeCamera::GlobeCameraController& m_globeCameraController;
                
            public:
                InteriorsExplorerCameraController(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                  Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                  Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                                  Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& m_globeCameraTouchController,
                                                  Eegeo::Camera::GlobeCamera::GlobeCameraController& globeCameraController);
                
                ~InteriorsExplorerCameraController();
                
                const Eegeo::Camera::CameraState GetCameraState() const;
                
                const Eegeo::Camera::RenderCamera GetRenderCamera() const;
                
                Eegeo::ITouchController& GetTouchController() const;
                
                Eegeo::Camera::GlobeCamera::GlobeCameraController& GetGlobeCameraController();
                
                void Update(float dt);
                
                void SetInterestLocation(const Eegeo::dv3& interestPointEcef);
                const Eegeo::dv3& GetInterestLocation() const;
                
                void SetDistanceToInterest(float distanceMeters);
                const float GetDistanceToInterest() const;
                
                void SetHeading(float headingDegrees);
                const float GetHeadingDegrees() const;
                
                void SetTilt(float tiltDegrees);
                
            private:
                
                float GetFloorOffsetHeight() const;
            };
        }
    }
}