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
#include "IRestrictedBuildingService.h"

namespace ExampleApp
{
    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class InteriorWorldPinController
            {
            public:
                
                InteriorWorldPinController(Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                           Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& markerRepository,
                                           WorldPins::SdkModel::IWorldPinsService& worldPinsService,
                                           Eegeo::Resources::Interiors::InteriorsCameraController& cameraController,
                                           ExampleAppMessaging::TMessageBus& messageBus,
                                           const InitialExperience::SdkModel::IInitialExperienceModel& initialExperienceModel,
                                           ExampleApp::WifiInfo::IRestrictedBuildingService& restrictedBuildingInformationService,
                                           const bool useIndoorEntryMarkerLabels);
                ~InteriorWorldPinController();
                
                const bool PinInteractionAllowed(const std::string& interiorId) const;
                const bool PinInteractionAllowedForCurrentNetwork(const std::string& interiorId) const;
                
                void Update(float dt);
                
                void SetInitialExperienceComplete();
                const void ShowAlert() const;                
                
            private:

                Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
                Eegeo::Resources::Interiors::Markers::InteriorMarkerModelRepository& m_markerRepository;
                WorldPins::SdkModel::IWorldPinsService& m_worldPinsService;
                Eegeo::Resources::Interiors::InteriorsCameraController& m_cameraController;
                std::map<std::string, WorldPins::SdkModel::WorldPinItemModel*> m_interiorIdToWorldPinMap;
                std::map<std::string, WorldPins::SdkModel::WorldPinItemModel*> m_deferedRemovalMap;
                ExampleAppMessaging::TMessageBus& m_messageBus;
                const InitialExperience::SdkModel::IInitialExperienceModel& m_initialExperienceModel;
                const bool m_useIndoorEntryMarkerLabels;
                bool m_menuIsDragging;
                
                Eegeo::Helpers::TCallback1<InteriorWorldPinController, const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel&> m_markerAddedCallback;
                Eegeo::Helpers::TCallback1<InteriorWorldPinController, const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel&> m_markerRemovedCallback;
                
                Eegeo::Helpers::TCallback1<InteriorWorldPinController, const Menu::MenuDragStateChangedMessage&> m_menuDraggedCallback;                
                ExampleApp::WifiInfo::IRestrictedBuildingService& m_restrictedBuildingInformationService;
                
                void HandleMarkerAdded(const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel& markerModel);
                void HandleMarkerRemoved(const Eegeo::Resources::Interiors::Markers::InteriorMarkerModel& markerModel);
                void HandleMenuDragged(const Menu::MenuDragStateChangedMessage& message);
            };
        }
    }
}