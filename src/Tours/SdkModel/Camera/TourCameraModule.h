// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Tours.h"
#include "IToursCameraModule.h"
#include "IToursCameraTransitionController.h"
#include "IToursCameraController.h"
#include "ResourceCeilingProvider.h"
#include "ScreenProperties.h"
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
                class TourCameraModule : public IToursCameraModule, private Eegeo::NonCopyable
                {
                    IToursCameraController* m_pToursCameraController;
                    IToursCameraTransitionController* m_pToursCameraTransitionController;
                    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController* m_pTouchController;
                    Eegeo::Resources::Interiors::InteriorsController& m_interiorController;
                    
                public:
                    TourCameraModule(Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                     const Eegeo::Rendering::ScreenProperties& screenProperties,
                                     Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& gpsGlobeCameraController,
                                     Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider,
                                     Eegeo::Resources::Interiors::InteriorsController& interiorController);

                    
                    ~TourCameraModule();
                    
                    IToursCameraController& GetToursCameraController() const;
                    
                    IToursCameraTransitionController& GetCameraTransitionController() const;
                    
                    Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& GetCameraTouchController() const;
                };
            }
        }
    }
}
