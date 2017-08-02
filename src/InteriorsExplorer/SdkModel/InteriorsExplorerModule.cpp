// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerModule.h"
#include "InteriorsExplorerViewModel.h"
#include "InteriorsExplorerModel.h"
#include "InteriorWorldPinController.h"
#include "GpsGlobeCameraController.h"
#include "InteriorsCameraControllerFactory.h"
#include "InteriorsCameraController.h"
#include "InteriorsGpsCameraControllerFactory.h"
#include "InteriorsGpsCameraController.h"
#include "GlobeCameraTouchController.h"
#include "InteriorVisibilityUpdater.h"
#include "InteriorExplorerUserInteractionModel.h"
#include "IInitialExperienceModel.h"
#include "InteriorsExplorerFloorDraggedObserver.h"
#include "InteriorPermissionObserver.h"
#include "InteriorSelectionController.h"


namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            InteriorsExplorerModule::InteriorsExplorerModule(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                             Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                             Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                                             Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                                             WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                                             const WorldPins::SdkModel::IWorldPinIconMapping& worldPinIconMapping,
                                                             const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                                             VisualMap::SdkModel::IVisualMapService& visualMapService,
                                                             const Eegeo::Resources::Interiors::InteriorsCameraControllerFactory& interiorCameraControllerFactory,
                                                             const Eegeo::Resources::Interiors::InteriorsGpsCameraControllerFactory& interiorGpsCameraControllerFactory,
                                                             const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                             Eegeo::Helpers::IIdentityProvider& identityProvider,
                                                             ExampleAppMessaging::TMessageBus& messageBus,
                                                             Metrics::IMetricsService& metricsService,
                                                             const InitialExperience::SdkModel::IInitialExperienceModel& initialExperienceModel,
                                                             const bool interiorsAffectedByFlattening,
                                                             PersistentSettings::IPersistentSettingsModel& persistentSettings,
                                                             Eegeo::Location::NavigationService& navigationService,
                                                             Eegeo::Resources::Interiors::MetaData::IInteriorMetaDataRepository& interiorMetaDataRepo,
                                                             TagSearch::View::ITagSearchRepository& tagSearchRepository,
                                                             Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory)
            : m_pInteriorSelectionController(NULL)
            {
                m_pUserInteractionModel = Eegeo_NEW(InteriorExplorerUserInteractionModel)();
                
                const float transitionTime = 0.5f;
                m_pVisibilityUpdater = Eegeo_NEW(InteriorVisibilityUpdater)(interiorTransitionModel, interiorSelectionModel, interiorInteractionModel, transitionTime);
                
                m_pGlobeCameraTouchController = interiorCameraControllerFactory.CreateTouchController();
                
                m_pGpsGlobeCameraController = interiorGpsCameraControllerFactory.CreateInteriorGpsGlobeCameraController(*m_pGlobeCameraTouchController);
                
                m_pInteriorsCameraController = interiorCameraControllerFactory.CreateInteriorsCameraController(*m_pGlobeCameraTouchController, m_pGpsGlobeCameraController->GetGlobeCameraController());
                
                m_pInteriorsGpsCameraController = interiorGpsCameraControllerFactory.CreateInteriorsGpsCameraController(*m_pInteriorsCameraController,
                                                                                                                        *m_pGlobeCameraTouchController,
                                                                                                                        *m_pGpsGlobeCameraController);
                
                
                m_pInteriorSelectionController = Eegeo_NEW(InteriorSelectionController)(interiorSelectionModel,
                                                                                        markerRepository,
                                                                                        *m_pInteriorsCameraController);
                
                m_pWorldPinController = Eegeo_NEW(InteriorWorldPinController)(interiorSelectionModel,
                                                                              messageBus,
                                                                              initialExperienceModel);
                
                m_pModel = Eegeo_NEW(InteriorsExplorerModel)(interiorInteractionModel,
                                                             interiorSelectionModel,
                                                             visualMapService,
                                                             messageBus,
                                                             metricsService,
                                                             persistentSettings);
                
                m_pViewModel = Eegeo_NEW(View::InteriorsExplorerViewModel)(false, identityProvider.GetNextIdentity(), messageBus);
                
                m_pFloorDraggedObserver = Eegeo_NEW(InteriorsExplorerFloorDraggedObserver)(*m_pModel, m_pInteriorsGpsCameraController->GetTouchController());
                
                m_pInteriorPermissionObserver = Eegeo_NEW(InteriorPermissionObserver)(interiorSelectionModel, alertBoxFactory);
            }
            
            InteriorsExplorerModule::~InteriorsExplorerModule()
            {
                Eegeo_DELETE m_pInteriorPermissionObserver;
                Eegeo_DELETE m_pFloorDraggedObserver;
                Eegeo_DELETE m_pViewModel;
                Eegeo_DELETE m_pModel;
                Eegeo_DELETE m_pWorldPinController;
                Eegeo_DELETE m_pInteriorsGpsCameraController;
                Eegeo_DELETE m_pInteriorsCameraController;
                Eegeo_DELETE m_pGpsGlobeCameraController;
                Eegeo_DELETE m_pVisibilityUpdater;
                Eegeo_DELETE m_pUserInteractionModel;
                Eegeo_DELETE m_pInteriorSelectionController;
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
            
            Eegeo::Resources::Interiors::InteriorsCameraController& InteriorsExplorerModule::GetInteriorsCameraController() const
            {
                return *m_pInteriorsCameraController;
            }
            
            Eegeo::Resources::Interiors::InteriorsGpsCameraController& InteriorsExplorerModule::GetInteriorsGpsCameraController() const
            {
                return *m_pInteriorsGpsCameraController;
            }
            
            void InteriorsExplorerModule::Update(float dt) const
            {
                m_pVisibilityUpdater->Update(dt);
            }
            
            InteriorsExplorerModel& InteriorsExplorerModule::GetInteriorsExplorerModel() const
            {
                return *m_pModel;
            }
            
            Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& InteriorsExplorerModule::GetTouchController() const
            {
                return *m_pGlobeCameraTouchController;
            }
            
            InteriorExplorerUserInteractionModel& InteriorsExplorerModule::GetInteriorsExplorerUserInteractionModel() const
            {
                return *m_pUserInteractionModel;
            }
        }
    }
}
