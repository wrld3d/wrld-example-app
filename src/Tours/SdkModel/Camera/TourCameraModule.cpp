// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "TourCameraModule.h"
#include "ToursCameraController.h"
#include "ToursCameraTransitionController.h"

namespace ExampleApp
{
    namespace Tours
    {
        namespace SdkModel
        {
            namespace Camera
            {
                TourCameraModule::TourCameraModule(Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                                   const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                   Eegeo::Camera::GlobeCamera::GpsGlobeCameraController& gpsGlobeCameraController,
                                                   Eegeo::Resources::Terrain::Heights::TerrainHeightProvider& terrainHeightProvider)
                {
                    Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchConfig = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();
                    
                    m_pTouchController = Eegeo_NEW(Eegeo::Camera::GlobeCamera::GlobeCameraTouchController)(touchConfig);
                    
                    m_pToursCameraController = Eegeo_NEW(ToursCameraController)(resourceCeilingProvider,
                                                                                *m_pTouchController,
                                                                                screenProperties);
                    
                    m_pToursCameraTransitionController = Eegeo_NEW(ToursCameraTransitionController)(*m_pToursCameraController,
                                                                                                    gpsGlobeCameraController,
                                                                                                    terrainHeightProvider,
                                                                                                    *m_pTouchController);

                }
                
                TourCameraModule::~TourCameraModule()
                {
                    Eegeo_DELETE m_pToursCameraTransitionController;
                    Eegeo_DELETE m_pToursCameraController;
                    Eegeo_DELETE m_pTouchController;
                }
                
                IToursCameraController& TourCameraModule::GetToursCameraController() const
                {
                    return *m_pToursCameraController;
                }
                
                IToursCameraTransitionController& TourCameraModule::GetCameraTransitionController() const
                {
                    return *m_pToursCameraTransitionController;
                }
                
                Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& TourCameraModule::GetCameraTouchController() const
                {
                    return *m_pTouchController;
                }
            }
        }
    }
}
