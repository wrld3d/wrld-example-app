// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Tours.h"
#include "SplineTransitionCameraMode.h"
#include "IToursCameraTransitionController.h"
#include "GlobeCamera.h"
#include "Terrain.h"
#include "Interiors.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                class ToursCameraTransitionController : public IToursCameraTransitionController, private Eegeo::NonCopyable
                {
                public:
                    
                    ToursCameraTransitionController(IToursCameraController& toursCameraController,
                                                    Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& gpsGlobeCameraController,
                                                    Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider);
                    
                    ~ToursCameraTransitionController();
                    
                    bool IsTransitionComplete() const;
                    
                    bool IsTransitioning() const;
                    
                    void Update(float dt);
                    
                    void SetAppCameraState(ToursCameraState& appCameraState);
                    
                    void TransitionTo(IToursCameraMode& targetCameraMode);
                    
                    void TransitionBackToAppCamera(bool returnToOriginalMode);
                    
                private:
                    
                    void PerformCameraTransitionOrFade(const ToursCameraState& currentState,
                                                       const ToursCameraState& desiredState);
                    
                    bool ShouldPerformCameraSpline(const ToursCameraState& currentState,
                                                   const ToursCameraState& desiredState);
                    
                    IToursCameraController& m_toursCameraController;
                    
                    // This class manages the lifetime of m_pToursTransitionMode.
                    IToursCameraTransitionMode* m_pToursTransitionMode;
                    
                    // This class does not manage the lifetime of the modes, but they are pointers as they are transient
                    // and replaceable. Assumption: the lifetime of the IToursCameraMode instances is longer than the time
                    //for which they are referenced by this class.
                    IToursCameraMode* m_pToursCurrentMode;
                    IToursCameraMode* m_pToursNextMode;

                    ToursCameraState m_appCameraState;
                    
                    Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& m_gpsGlobeCameraController;
                    Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& m_terrainHeightProvider;
                };
            }
        }
    }
}
