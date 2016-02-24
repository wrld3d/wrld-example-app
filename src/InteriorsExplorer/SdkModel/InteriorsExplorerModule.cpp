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
#include "InteriorExplorerUserInteractionModel.h"
#include "IInitialExperienceModel.h"

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
                                                             const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                             VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                             Eegeo::Camera::GlobeCamera::GlobeCameraControllerFactory& globeCameraControllerFactory,
                                                             const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                             Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                             ExampleAppMessaging::TMessageBus& messageBus,
                                                             Metrics::IMetricsService& metricsService,
                                                             const InitialExperience::SdkModel::IInitialExperienceModel& initialExperienceModel,
                                                             const bool interiorsAffectedByFlattening)
            {
                m_pUserInteractionModel = Eegeo_NEW(InteriorExplorerUserInteractionModel)();
                
                const float transitionTime = 0.5f;
                m_pVisibilityUpdater = Eegeo_NEW(InteriorVisibilityUpdater)(interiorController, transitionTime);
                
                Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration touchConfig = Eegeo::Camera::GlobeCamera::GlobeCameraTouchControllerConfiguration::CreateDefault();
                Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration globeCameraConfig = Eegeo::Camera::GlobeCamera::GlobeCameraControllerConfiguration::CreateDefault(false);
                
                globeCameraConfig.terrainFollowingEnabled = false;
                globeCameraConfig.zoomAltitudeLow = 50.0f;
                globeCameraConfig.maxAltitude = 1700.f;
                globeCameraConfig.computeNearFarPlanes = false;
                // near and far multipliers aproximated from cos( 65 ) so should allow for tilt + fov = 65
                globeCameraConfig.nearPlane = 0.4f * globeCameraConfig.zoomAltitudeLow;
                globeCameraConfig.farPlane = 2.5f * globeCameraConfig.maxAltitude;
                
                m_pGlobeCameraTouchController = globeCameraControllerFactory.CreateTouchController(touchConfig, screenProperties);
                
                m_pGlobeCameraController = globeCameraControllerFactory.CreateCameraController(globeCameraConfig,
                                                                                               *m_pGlobeCameraTouchController,
                                                                                               screenProperties);
                
                m_pInteriorsCameraController = Eegeo_NEW(InteriorsExplorerCameraController)(interiorController,
                                                                                            interiorSelectionModel,
                                                                                            environmentFlatteningService,
                                                                                            *m_pGlobeCameraTouchController,
                                                                                            *m_pGlobeCameraController,
                                                                                            interiorsAffectedByFlattening);
                
                m_pWorldPinController = Eegeo_NEW(InteriorWorldPinController)(interiorController,
                                                                              markerRepository,
                                                                              worldPinsService,
                                                                              *m_pInteriorsCameraController,
                                                                              messageBus,
                                                                              initialExperienceModel);
                
                m_pModel = Eegeo_NEW(InteriorsExplorerModel)(interiorController,
                                                             interiorSelectionModel,
                                                             visualMapService,
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
                Eegeo_DELETE m_pUserInteractionModel;
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
                m_pWorldPinController->Update(dt);
            }
            
            
            InteriorsExplorerModel& InteriorsExplorerModule::GetInteriorsExplorerModel() const
            {
                return *m_pModel;
            }
            
            InteriorExplorerUserInteractionModel& InteriorsExplorerModule::GetInteriorsExplorerUserInteractionModel() const
            {
                return *m_pUserInteractionModel;
            }
        }
    }
}