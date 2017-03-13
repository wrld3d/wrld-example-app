// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "InteriorsExplorer.h"
#include "Interiors.h"
#include "Types.h"
#include "IInteriorsExplorerModule.h"
#include "WorldPins.h"
#include "GlobeCamera.h"
#include "Rendering.h"
#include "BidirectionalBus.h"
#include "SdkModelDomainEventBus.h"
#include "Metrics.h"
#include "IIdentity.h"
#include "VisualMap.h"
#include "InitialExperience.h"
#include "PersistentSettings.h"
#include "NavigationService.h"
#include "InteriorMetaDataRepository.h"
#include "TagSearchRepository.h"
#include "IAlertBoxFactory.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorsExplorerModule : public IInteriorsExplorerModule, private Eegeo::NonCopyable
            {
            public:
                InteriorsExplorerModule(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
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
                                        Eegeo::UI::NativeAlerts::IAlertBoxFactory& alertBoxFactory);

                ~InteriorsExplorerModule();
                
                View::InteriorsExplorerViewModel& GetInteriorsExplorerViewModel() const;
                
                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const;
                
                Eegeo::Resources::Interiors::InteriorsCameraController& GetInteriorsCameraController() const;
                
                Eegeo::Resources::Interiors::InteriorsGpsCameraController& GetInteriorsGpsCameraController() const;
                
                InteriorVisibilityUpdater& GetInteriorVisibilityUpdater() const;
                
                void Update(float dt) const;
                
                InteriorsExplorerModel& GetInteriorsExplorerModel() const;
                
                Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& GetTouchController() const;
                
                InteriorExplorerUserInteractionModel& GetInteriorsExplorerUserInteractionModel() const;
                
            private:
                InteriorsExplorerModel* m_pModel;
                View::InteriorsExplorerViewModel* m_pViewModel;
                InteriorVisibilityUpdater* m_pVisibilityUpdater;
                InteriorExplorerUserInteractionModel* m_pUserInteractionModel;
                InteriorsExplorerFloorDraggedObserver* m_pFloorDraggedObserver;
                InteriorPermissionObserver* m_pInteriorPermissionObserver;
                
                InteriorWorldPinController* m_pWorldPinController;
                InteriorSelectionController* m_pInteriorSelectionController;
                Eegeo::Resources::Interiors::InteriorsCameraController* m_pInteriorsCameraController;
                Eegeo::Resources::Interiors::InteriorsGpsCameraController* m_pInteriorsGpsCameraController;
                Eegeo::Camera::GlobeCamera::GlobeCameraTouchController* m_pGlobeCameraTouchController;
                Eegeo::Camera::GlobeCamera::GpsGlobeCameraController* m_pGpsGlobeCameraController;

            };
        }
    }
}
