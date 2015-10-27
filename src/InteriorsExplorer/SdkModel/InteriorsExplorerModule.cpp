// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerModule.h"
#include "InteriorsExplorerCameraController.h"
#include "InteriorsExplorerViewModel.h"
#include "InteriorsExplorerModel.h"
#include "InteriorWorldPinController.h"
#include "GlobeCameraController.h"
#include "GlobeCameraControllerFactory.h"
#include "GlobeCameraTouchController.h"
#include "GlobeCameraTouchControllerConfiguration.h"
#include "GlobeCameraControllerConfiguration.h"
#include "InteriorVisibilityUpdater.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorsExplorerModule::InteriorsExplorerModule(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                                             Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                             Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                                             WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                             ExampleApp::MapMode::SdkModel::IMapModeModel& mapModeModel,
                                                             WeatherMenu::SdkModel::IWeatherController& weatherController,
                                                             Eegeo::Camera::GlobeCamera::GlobeCameraControllerFactory& globeCameraControllerFactory,
                                                             const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                             Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                             ExampleAppMessaging::TMessageBus& messageBus,
                                                             Metrics::IMetricsService& metricsService)
            {
                
                const float transitionTime = 0.5f;
                m_pVisibilityUpdater = Eegeo_NEW(InteriorVisibilityUpdater)(interiorController, transitionTime);
                
                Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchConfig = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();
                Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration globeCameraConfig = Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration::CreateDefault(false);
                
                globeCameraConfig.terrainFollowingEnabled = false;
                globeCameraConfig.zoomAltitudeLow = 5.0f;
                globeCameraConfig.fovZoomedInCity = 45.0f;
                globeCameraConfig.fovZoomedInGlobe = 90.0f;
                globeCameraConfig.maxAltitude = 250.0f;
                globeCameraConfig.computeNearFarPlanes = false;
                globeCameraConfig.nearPlane = 1.f;
                globeCameraConfig.farPlane = 5000.f;
                
                m_pGlobeCameraTouchController = globeCameraControllerFactory.CreateTouchController(touchConfig, screenProperties);
                
                m_pGlobeCameraController = globeCameraControllerFactory.CreateCameraController(globeCameraConfig,
                                                                                               *m_pGlobeCameraTouchController,
                                                                                               screenProperties);
                
                m_pInteriorsCameraController = Eegeo_NEW(InteriorsExplorerCameraController)(interiorController,
                                                                                            interiorSelectionModel,
                                                                                            markerRepository,
                                                                                            *m_pGlobeCameraTouchController,
                                                                                            *m_pGlobeCameraController);
                
                m_pWorldPinController = Eegeo_NEW(InteriorWorldPinController)(interiorController,
                                                                              markerRepository,
                                                                              worldPinsService,
                                                                              *m_pInteriorsCameraController,
                                                                              messageBus);
                
                m_pModel = Eegeo_NEW(InteriorsExplorerModel)(interiorController,
                                                             interiorSelectionModel,
                                                             *m_pVisibilityUpdater,
                                                             mapModeModel,
                                                             weatherController,
                                                             messageBus,
                                                             metricsService);
                
                m_pViewModel = Eegeo_NEW(View::InteriorsExplorerViewModel)(false, identityProvider.GetNextIdentity());
            }
            
            InteriorsExplorerModule::~InteriorsExplorerModule()
            {
                Eegeo_DELETE m_pViewModel;
                Eegeo_DELETE m_pModel;
                Eegeo_DELETE m_pWorldPinController;
                Eegeo_DELETE m_pInteriorsCameraController;
                Eegeo_DELETE m_pGlobeCameraTouchController;
                Eegeo_DELETE m_pGlobeCameraController;
                Eegeo_DELETE m_pVisibilityUpdater;
            }
            
            View::InteriorsExplorerViewModel& InteriorsExplorerModule::GetInteriorsExplorerViewModel() const
            {
                return *m_pViewModel;
            }
            
            ScreenControl::View::IScreenControlViewModel& InteriorsExplorerModule::GetScreenControlViewModel() const
            {
                return *m_pViewModel;
            }
            
            InteriorVisibilityUpdater& InteriorsExplorerModule::GetInteriorVisibilityUpdater() const
            {
                return *m_pVisibilityUpdater;
            }
            
            InteriorsExplorerCameraController& InteriorsExplorerModule::GetInteriorsCameraController() const
            {
                return *m_pInteriorsCameraController;
            }
            
            void InteriorsExplorerModule::Update(float dt) const
            {
                m_pVisibilityUpdater->Update(dt);
            }
            
            
            InteriorsExplorerModel& InteriorsExplorerModule::GetInteriorsExplorerModel() const
            {
                return *m_pModel;
            }
        }
    }
}