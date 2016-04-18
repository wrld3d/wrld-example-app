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
                                        WorldPins::SdkModel::IWorldPinsScaleController& worldPinsScaleController,
                                        const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService,
                                        VisualMap::SdkModel::IVisualMapService& visualMapService,
                                        const Eegeo::Resources::Interiors::InteriorsCameraControllerFactory& interiorCameraControllerFactory,
                                        const Eegeo::Rendering::ScreenProperties& screenProperties,
                                        Eegeo::Helpers::IIdentityProvider& identityProvider,
                                        ExampleAppMessaging::TMessageBus& messageBus,
                                        Metrics::IMetricsService& metricsService,
                                        const InitialExperience::SdkModel::IInitialExperienceModel& initialExperienceModel,
                                        const bool interiorsAffectedByFlattening);

                ~InteriorsExplorerModule();
                
                View::InteriorsExplorerViewModel& GetInteriorsExplorerViewModel() const;
                
                ScreenControl::View::IScreenControlViewModel& GetScreenControlViewModel() const;
                
                Eegeo::Resources::Interiors::InteriorsCameraController& GetInteriorsCameraController() const;
                
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
                
                InteriorWorldPinController* m_pWorldPinController;
                Eegeo::Resources::Interiors::InteriorsCameraController* m_pInteriorsCameraController;
                Eegeo::Camera::GlobeCamera::GlobeCameraTouchController* m_pGlobeCameraTouchController;
                Eegeo::Camera::GlobeCamera::GlobeCameraController* m_pGlobeCameraController;
            };
        }
    }
}