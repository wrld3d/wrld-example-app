// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Interiors.h"
#include "WorldPins.h"
#include "ICallback.h"
#include "InteriorsExplorer.h"
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
            class InteriorWorldPinController
            {
            public:
                
                InteriorWorldPinController(Eegeo::Resources::Interiors::InteriorController& interiorController,
                                           Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                           WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                           InteriorsExplorerCameraController& cameraController,
                                           ExampleAppMessaging::TMessageBus& messageBus,
                                           const InitialExperience::SdkModel::IInitialExperienceModel& initialExperienceModel);
                ~InteriorWorldPinController();
                
                const bool PinInteractionAllowed(const std::string& interiorId) const;
                
                void Update(float dt);
                
                void SetInitialExperienceComplete();
                
            private:
                
                Eegeo::Resources::Interiors::InteriorController& m_interiorController;
                Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& m_markerRepository;
                WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                InteriorsExplorerCameraController& m_cameraController;
                std::map<std::string, WorldPins::SdkModel::WorldPinItemModel*> m_interiorIdToWorldPinMap;
                std::map<std::string, WorldPins::SdkModel::WorldPinItemModel*> m_deferedRemovalMap;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                const InitialExperience::SdkModel::IInitialExperienceModel& m_initialExperienceModel;
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