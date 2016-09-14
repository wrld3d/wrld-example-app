// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Interiors.h"
#include "WorldPins.h"
#include "ICallback.h"
#include "InteriorsExplorer.h"
#include "IInteriorCameraController.h"
#include <map>
#include <string>
#include "BidirectionalBus.h"
#include "InitialExperience.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorWorldPinController : private Eegeo::NonCopyable
            {
            public:
                
                InteriorWorldPinController(const std::shared_ptr<Eegeo::Resources::Interiors::InteriorSelectionModel>& interiorSelectionModel,
                                           const std::shared_ptr<Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository>& markerRepository,
                                           const std::shared_ptr<WorldPins::SdkModel::IWorldPinsService>& worldPinsService,
                                           const std::shared_ptr<IInteriorCameraController>& cameraController,
                                           const std::shared_ptr<ExampleAppMessaging::TMessageBus>& messageBus,
                                           const std::shared_ptr<InitialExperience::SdkModel::IInitialExperienceModel>& initialExperienceModel);
                ~InteriorWorldPinController();
                
                const bool PinInteractionAllowed(const std::string& interiorId) const;
                
                void Update(float dt);
                
                void SetInitialExperienceComplete();
                
            private:

                const std::shared_ptr<Eegeo::Resources::Interiors::InteriorSelectionModel> m_interiorSelectionModel;
                const std::shared_ptr<Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository> m_markerRepository;
                const std::shared_ptr<WorldPins::SdkModel::IWorldPinsService> m_worldPinsService;
                const std::shared_ptr<IInteriorCameraController> m_cameraController;
                std::map<std::string, WorldPins::SdkModel::WorldPinItemModel*> m_interiorIdToWorldPinMap;
                std::map<std::string, WorldPins::SdkModel::WorldPinItemModel*> m_deferedRemovalMap;
                const std::shared_ptr<ExampleAppMessaging::TMessageBus> m_messageBus;
                const std::shared_ptr<const InitialExperience::SdkModel::IInitialExperienceModel> m_initialExperienceModel;
                bool m_menuIsDragging;
                
                Eegeo::Helpers::TCallback1<InteriorWorldPinController, const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel&> m_markerAddedCallback;
                Eegeo::Helpers::TCallback1<InteriorWorldPinController, const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel&> m_markerRemovedCallback;
                
                Eegeo::Helpers::TCallback1<InteriorWorldPinController, const Menu::MenuDragStateChangedMessage&> m_menuDraggedCallback;
                
                void HandleMarkerAdded(const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel& markerModel);
                void HandleMarkerRemoved(const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel& markerModel);
                void HandleMenuDragged(const Menu::MenuDragStateChangedMessage& message);
            };
        }
    }
}